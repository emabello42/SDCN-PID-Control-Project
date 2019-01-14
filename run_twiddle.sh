#!/bin/bash
# script to run the pid controller with twiddle activated with the following parameters:
# Kp Ki Kd throttle 1 <number of iterations used to calculate the error>
./build/pid  0.281804 0.000101439 3.01659 0.3 1 1400
