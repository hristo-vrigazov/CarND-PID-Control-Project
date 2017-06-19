//
// Created by hvrigazov on 18.06.17.
//

#ifndef PID_PARAMETERTUNER_H
#define PID_PARAMETERTUNER_H

#include <functional>
#include "Parameters.h"


class ParameterTuner {
public:
    void FindBest(Parameters & initialValues, std::function<void(Parameters)> callback);

private:
    Parameters RunFinished(double error);
    Parameters bestEstimate;
    double parameterChanges[4];

    double bestError;
    unsigned i;

    double thresholdError;
    bool direction;
    std::function<void(Parameters)> callback;
};


#endif //PID_PARAMETERTUNER_H
