//
// Created by hvrigazov on 18.06.17.
//

#ifndef PID_PARAMETERS_H
#define PID_PARAMETERS_H

#include <cstdlib>
#include <vector>

class Parameters {
public:
    Parameters(char* argv[]);

    Parameters(double Kp, double Ki, double Kd, double throttle);

    Parameters();

    double * getParameters();

    double getKp();
    double getKi();
    double getKd();
    double getThrottle();

private:
    double parametersArray[4];
};


#endif //PID_PARAMETERS_H
