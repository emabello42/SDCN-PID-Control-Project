## Project: PID controller
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Overview
---
In this project a PID controller is implemented in C++ to maneuver a vehicle around a track!
The Udacity's simulator provides the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle.

---

## Dependencies
[image1]: ./img/effect_of_p.gif "Effect of P"
[image2]: ./img/effect_of_d.gif "Effect of D"
[image3]: ./img/effect_of_i.gif "Effect of I"
[image4]: ./img/effect_of_small_i.gif "Effect of small I"

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
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

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Run the following script to compile: `build.sh`
3. Run it with: `run.sh`
4. Optionally run it, with the twiddle algorithm activated as follows: `run_twiddle.sh`

This will update Kp, Ki and Kd coefficients (used in the proportional, integral and derivative terms, respectively)  used by the PID controller and report the best combination of them (if found).

## Effect of each component of the PID controller.

If only the proportional component `P` is considered in the controller (i.e. all
the other components are set to zero), this will drive the car as shown in the
video below (in this case: `Kp=1, Ki=0, Kd=0`):

![alt text][image1]

As can be seen, the car steers hard every time to the left and then to the right.
This is due to the fact that P is proportional to the opposite of CTE (in
this case: the distance to the lane center), thus steering always in the opposite direction of the error.

But, if the derivate component 'D' is activated, the controller produces an output as shown below (in this case: `Kp=1, Ki=0, Kd=1`):

![alt text][image2]

The `D` component helps to smooth the steering angle generated, because `D` is calculated as the
difference between the current and the previous CTE (divided by the difference in time), thus gradually reducing the steering
angle generated as the error decreases.


If the integral component `I` is activated, the controller will produce the following behavior (in this case: `Kp=1, Ki=1, Kd=1`):

![alt text][image3]

In this case, the 'I' component, which is the opposite of the sum of previous CTEs, is generating too large steering angles. But if `Ki` coefficient is reduced, this can help to produce better results as shown below (in this case: `Kp=1, Ki=0.0001, Kd=1`):

![alt text][image4]

## Final hyperparameters (Kp, Ki, Kd coefficients)
The final values for `Kp`, `Ki` and `Kd` were calculated using the Twiddle algorithm (implemented in `src/twiddle.cpp`). This algorithm updates one single coefficient every time, searching for the best combination of them, i.e. that produces the smallest possible error.
In this implementation, Twiddle updates every coeffcient every 1400 iterations (every iteration corresponds to a call from the simulator providing the current speed, angle and CTE values), and compares the squared sum of CTEs with the obtained one previously. 1400 iterations corresponds to a complete lap.

Before the first run of twiddle, the coefficients were manually initialized. In this case, a similar combination to the proposed in the lessons worked quite well, namely: Kp=0.2, Ki=0.0001, Kd= 3. Then, after running Twiddle, these were the final coefficient values:
Kp=0.281804, Ki=0.000101439, Kd=3.01659

