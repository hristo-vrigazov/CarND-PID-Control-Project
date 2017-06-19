# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## How to run

```
mkdir build && cd build
cmake .. && make
./pid 0.05 0.004 1.3 0.2
```

## PID controller explanation

The problem we are trying to solve is the following: we are trying to follow a given trajectory
with our autonomous car. The CTE (cross track error) is measure of how well the car is doing. The PID controller
is an algorithm which, based on the three components below, solves this problem.

* Proportional - makes the output value proportional to the CTE.
* Integral - takes care of accumulated error that has not been corrected.
* Derivative - tries to predict system behavior

## Parameter tuning - Twiddle

The feasible parameters are found using twiddle. The class `Parameters` represents the
parameters we are searching for, and can be instantiated by parsing command line arguments. The `main.cpp` file
runs in two modes: train and execution. To run it in train, run:
```
./pid -t
```
This will initialize the parameters and start searching using twiddle. The search is performed by the class
`ParameterTuner` by calling the method `FindBest`, which accepts the initial parameters and a callback for when the
best parameters are found. In the `main.cpp` file, we initialize some random parameters and pass in callback that prints
the best found parameters. For given parameters, we evaluate then every execution by calculating how fast it gets
to a fixed CTE (we are using 100.0, which is enough to get around the track once). But since we want more elapsed time
to be worse, we need to make the error function `1 / elapsed time`. But the values here could get pretty small so we take
the log of it. So the error becomes something like `double error = log(1. / (std::clock() - start));`. The twiddle implemented
in `ParameterTuner#RunFinished` method runs until a specified error threshold is exceeded. In our case, -13.5 seemed good enough.

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
