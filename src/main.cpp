#include <uWS/uWS.h>
#include "ParameterTuner.h"
#include "Execution.h"

int main(int argc, char* argv[])
{
  if (strcmp(argv[1], "-t") == 0) {
    std::cout << "Training" << std::endl;
    ParameterTuner parameterTuner;
    Parameters initialParameters(0.10, 0.01, 1.0, 0.2);
    Parameters bestParameters = parameterTuner.FindBest(initialParameters);
    std::cout << "Best parameters found." << std::endl;
    std::cout << "Run: " << std::endl;
    std::cout << "./pid " << bestParameters.getKp() << ' '
                          << bestParameters.getKi() << ' '
                          << bestParameters.getKd() << ' '
                          << bestParameters.getThrottle() << ' '
                          << std::endl;
    return 0;
  }

  Parameters parameters(argv);
  Execution execution;
  execution.run(parameters);
  return 0;
}
