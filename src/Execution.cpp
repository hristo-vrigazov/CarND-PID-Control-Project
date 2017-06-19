//
// Created by hvrigazov on 18.06.17.
//

#include "Execution.h"

Execution::Execution(std::function<Parameters(double)> callback,
                     double cte_threshold,
                     double error_threshold,
                     std::function<void(Parameters)> parametersFoundCallback) {
  this->callback = callback;
  this->sum_of_squares_cte_threshold = cte_threshold;
  this->sum_of_squares_cte = 0;
  this->error_threshold = error_threshold;
  this->parametersFoundCallback = parametersFoundCallback;
}


void Execution::run(double Kp, double Ki, double Kd, double throttle, bool restartWhenCTEExceeds) {
  uWS::Hub h;

  PID pid;
  pid.Init(Kp, Ki, Kd);

  sum_of_squares_cte = 0;
  std::clock_t start = std::clock();

  h.onMessage([&pid, &throttle, &start, &restartWhenCTEExceeds, this](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
      // "42" at the start of the message means there's a websocket message event.
      // The 4 signifies a websocket message
      // The 2 signifies a websocket event
      if (length && length > 2 && data[0] == '4' && data[1] == '2')
      {
        auto s = hasData(std::string(data).substr(0, length));
        if (s != "") {
          auto j = json::parse(s);
          std::string event = j[0].get<std::string>();
          if (event == "telemetry") {
            // j[1] is the data JSON object

            double cte = std::stod(j[1]["cte"].get<std::string>());
            double speed = std::stod(j[1]["speed"].get<std::string>());
            double angle = std::stod(j[1]["steering_angle"].get<std::string>());
            double steer_value;
            /*
            * TODO: Calcuate steering value here, remember the steering value is
            * [-1, 1].
            * NOTE: Feel free to play around with the throttle and speed. Maybe use
            * another PID controller to control the speed!
            */

            pid.UpdateError(cte);
            steer_value = pid.TotalError();
            // DEBUG
//            std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

            sum_of_squares_cte += cte * cte;
//            std::cout << sum_of_squares_cte << std::endl;

            if (restartWhenCTEExceeds) {
              if (sum_of_squares_cte > sum_of_squares_cte_threshold) {
                double error = log(1. / (std::clock() - start));
                if (error < error_threshold) {
                  std::string msg("42[\"reset\", {}]");
                  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                  this->parametersFoundCallback(Parameters(pid.Kp, pid.Ki, pid.Kd, throttle));
                  exit(0);
                }
                Parameters new_parameters = callback(error);
                std::string msg("42[\"reset\", {}]");
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                sum_of_squares_cte = 0;
                start = std::clock();
                std::cout << new_parameters.getKp() << ' ' << new_parameters.getKi() << ' ' << new_parameters.getKd()
                          << ' '
                          << new_parameters.getThrottle() << std::endl;
                pid.Init(new_parameters.getKp(), new_parameters.getKi(), new_parameters.getKd());
                throttle = new_parameters.getThrottle();
              }
            }


            json msgJson;
            msgJson["steering_angle"] = steer_value;
            msgJson["throttle"] = throttle;
            auto msg = "42[\"steer\"," + msgJson.dump() + "]";
//            std::cout << msg << std::endl;
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          }
        } else {
          // Manual driving
          std::string msg = "42[\"manual\",{}]";
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
      const std::string s = "<h1>Hello world!</h1>";
      if (req.getUrl().valueLength == 1)
      {
        res->end(s.data(), s.length());
      }
      else
      {
        // i guess this should be done more gracefully?
        res->end(nullptr, 0);
      }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
      std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
      ws.close();
      std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
  }
  h.run();
}


std::string Execution::hasData(std::string s){
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

void Execution::run(Parameters parameters, bool restartWhenCTEExceeds) {
  this->run(parameters.getKp(), parameters.getKi(), parameters.getKd(), parameters.getThrottle(), restartWhenCTEExceeds);
}
