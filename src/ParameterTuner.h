//
// Created by hvrigazov on 18.06.17.
//

#ifndef PID_PARAMETERTUNER_H
#define PID_PARAMETERTUNER_H

#include "Parameters.h"


class ParameterTuner {
public:
    Parameters FindBest(Parameters & initialValues);

private:
    Parameters RunFinished(double error);
    Parameters bestEstimate;
    double parameterChanges[4];

    double bestError;
    unsigned i;

    bool direction;
};


#endif //PID_PARAMETERTUNER_H
