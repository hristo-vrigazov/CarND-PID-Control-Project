//
// Created by hvrigazov on 18.06.17.
//

#ifndef PID_EXECUTION_H
#define PID_EXECUTION_H


#include <functional>
#include <uWS/uWS.h>
#include "json.hpp"
#include "PID.h"
#include "Parameters.h"
#include <ctime>

// for convenience
using json = nlohmann::json;

class Execution {
public:
    Execution(std::function<Parameters(double)> callback = [](double a){ return Parameters();},
              double cte_threshold = 100.0);
    void run(double Kp, double Ki, double Kd, double throttle, bool restartWhenCTEExceeds = false);
    void run(Parameters parameters, bool restartWhenCTEExceeds = false);
private:
    std::function<Parameters(double)> callback;
    double sum_of_squares_cte_threshold;
    double sum_of_squares_cte;
    std::string hasData(std::string s);
};


#endif //PID_EXECUTION_H
