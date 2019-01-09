#include "PID.h"
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {

}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->prev_cte = 0;
    this->cte_sum = 0;
}

void PID::UpdateError(double cte) {
    double delta = cte - prev_cte;
    cte_sum += cte;
    p_error = Kp*cte;
    i_error =Ki*cte_sum;
    d_error = Kd*delta;
    prev_cte = cte;
}

double PID::TotalError() {
    return p_error + i_error + d_error;
}
