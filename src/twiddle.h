#ifndef TWIDDLE_H
#define TWIDDLE_H
#include <vector>

using namespace std;

class Twiddle {
public:
    Twiddle(vector<double> p, int cycle, double tol=0.2)
    {
        this->p = p;
        this->tol = tol;
        for(int i=0; i < p.size(); i++)
        {
            this->dp.push_back(1.0);
            this->p_phase.push_back(0);
        }
        p_idx = 0;
        update_cycle = cycle;
        error_initialized = false;
        active_timer = false;
        timer = 0;
        err = 0;

    }
    vector<double> run(double err);

private:
    vector<double> p;
    vector<double> dp;
    vector<int> p_phase;
    double tol;
    double best_err;
    int p_idx;
    int update_cycle;
    bool error_initialized;
    bool active_timer;
    int timer;
    double err;
};
#endif
