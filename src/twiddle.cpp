#include "twiddle.h"
#include <iostream>
vector<double> Twiddle::run(double cte, bool & update)
{
    timer++;
    err += cte*cte;
        double dp_sum = 0.0;
        for(size_t i = 0; i < dp.size(); i++)
        {
            dp_sum += dp[i];
        }
    if(!error_initialized)
    {
        if((timer % update_cycle) == 0)
        {
            cout << endl;
            cout << "Twiddle iteration: "<< timer << " error:"<< err << endl;
            update = true;
            best_err = err;
            error_initialized = true;
            p[p_idx] += dp[p_idx];
            err = 0;
        }
    }
    else if( (timer % update_cycle) == 0)
    {
        cout << endl;
        cout << "Twiddle iteration: "<< timer << " error:"<< err << endl;
        update = true;
        if(dp_sum <= tol)
        {
            cout << "dp_sum = "<< dp_sum << endl;
            return p;
        }
        switch(p_phase[p_idx])
        {
            case 0:
                if(err < best_err)
                {
                    cout << "#########################################"<< endl;
                    cout << "NEW BEST ERR!: " << err << endl;
                    for(size_t i=0; i < p.size(); i++)
                    {
                        cout << p[i] << " ";
                    }
                    cout <<  endl;
                    cout << "#########################################"<< endl;
                    best_err = err;
                    dp[p_idx] *= 1.1;
                }
                else
                {
                    p[p_idx] -= 2*dp[p_idx];
                    p_phase[p_idx] = 1;
                }
                p_idx = (p_idx + 1) % dp.size();
                break;

            case 1:
                dp[p_idx] *= 0.9;
                p_phase[p_idx] = 0;
                break;
        }//end switch
        p[p_idx] += dp[p_idx];
        err = 0;
    }
    return p;
}
