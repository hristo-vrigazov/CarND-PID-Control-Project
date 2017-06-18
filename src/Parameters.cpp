//
// Created by hvrigazov on 18.06.17.
//

#include "Parameters.h"

Parameters::Parameters(double Kp, double Ki, double Kd, double throttle) {
  this->parametersArray[0] = Kp;
  this->parametersArray[1] = Ki;
  this->parametersArray[2] = Kd;
  this->parametersArray[3] = throttle;
}

Parameters::Parameters(char **argv) : Parameters(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4])) {}

double * Parameters::getParameters() {
  return parametersArray;
}

Parameters::Parameters() : Parameters(1.0, 0.0, 0.0, 0.2) {}

double Parameters::getKp() {
  return parametersArray[0];
}

double Parameters::getKi() {
  return parametersArray[1];
}

double Parameters::getKd() {
  return parametersArray[2];
}

double Parameters::getThrottle() {
  return parametersArray[3];
}
