//
// Created by hvrigazov on 18.06.17.
//

#include "ParameterTuner.h"
#include "Execution.h"

Parameters ParameterTuner::FindBest(Parameters & initialValues) {
  for (unsigned i = 0; i < 4; i++) {
    this->parameterChanges[i] = 1.0;
  }

  this->bestEstimate = initialValues;
  this->i = 0;
  this->direction = false;
  auto func = [this] (double error) {
      return this->RunFinished(error);
  };
  Execution execution(func, 20.0);
  execution.run(initialValues, true);
  return initialValues;
}

Parameters ParameterTuner::RunFinished(double error) {

  if (direction) {
    if (error < bestError) {
      bestError = error;
      parameterChanges[i] *= 1.1;
    } else {
      bestEstimate.getParameters()[i] -= 2 * parameterChanges[i];
    }
    direction = false;
    return bestEstimate;
  }

  if (error < bestError) {
    bestError = error;
    parameterChanges[i] *= 1.1;
  } else {
    bestEstimate.getParameters()[i] += parameterChanges[i];
    parameterChanges[i] *= 0.9;
    i++;
  }

  direction = true;
  return bestEstimate;
}
