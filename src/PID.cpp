#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp; // proportional
  this->Ki = Ki; // integral
  this->Kd = Kd; // differential

  p_error = 1.0;  // proportional cte
  i_error = 0.0; // integral cte
  d_error = 0.0; // differential cte
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}

