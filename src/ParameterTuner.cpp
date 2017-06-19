//
// Created by hvrigazov on 18.06.17.
//

#include "ParameterTuner.h"
#include "Execution.h"

void ParameterTuner::FindBest(Parameters & initialValues, std::function<void(Parameters)> callback) {
  for (unsigned i = 0; i < 4; i++) {
    this->parameterChanges[i] = 1.0;
  }

  this->bestEstimate = initialValues;
  this->i = 0;
  this->direction = false;
  auto func = [this] (double error) {
      return this->RunFinished(error);
  };
  Execution execution(func, 100.0, -13.5, callback);
  execution.run(initialValues, true);
}

Parameters ParameterTuner::RunFinished(double error) {

  std::cout << "Error: " << error << std::endl;

  if (direction) {
    if (error < bestError) {
      std::cout << "Error improved, direction " << direction << std::endl;
      bestError = error;
      parameterChanges[i] *= 1.1;
    } else {
      std::cout << "Error did not improve , direction " << direction << std::endl;
      bestEstimate.getParameters()[i] -= 2 * parameterChanges[i];
    }
    direction = false;
    return bestEstimate;
  }

  if (error < bestError) {
    std::cout << "Error improved, direction " << direction << std::endl;

    bestError = error;
    parameterChanges[i] *= 1.1;
  } else {
    std::cout << "Error did not improve , direction " << direction << std::endl;

    bestEstimate.getParameters()[i] += parameterChanges[i];
    parameterChanges[i] *= 0.9;
  }

  i = ((i + 1) % 4);
  bestEstimate.getParameters()[i] += parameterChanges[i];
  direction = true;
  return bestEstimate;
}
