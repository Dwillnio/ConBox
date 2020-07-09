#ifndef STOCH_LEAST_SQUARES
#define STOCH_LEAST_SQUARES

#include "det_least_squares.h"

class stoch_rlse
{
    stoch_rlse(const matrix& M0_, const vec& theta0_, nnum order_, bool causal_ = 1)
        : order(order_), causal(causal_), P(M0_.cols(), M0_.cols()), M(M0_), y_prev(0), theta(theta0_)
    {
        Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(M0_);
        if(M.rank() == M.cols()){
            P = (M.transpose() * M).inverse();
            full_rank = true;
        } else {
            full_rank = false;
        }
    }

    vec compute(const vec& m_new, rnum y_new, rnum r_v);
    vec compute(rnum y_new, rnum u_new, rnum r_v);

protected:
    nnum order;
    bool full_rank, causal;
    matrix P, M;
    rnum y_prev;
    vec theta;
};

std::pair<vec,matrix> most_likely_solution(const matrix& m, const vec& y,
                                           const matrix& R_th, const matrix& R_v, const matrix& R_thv);

std::pair<vec,matrix> most_likely_solution(const matrix& m, const vec& y,
                                           const matrix& R_th, const matrix& R_v);

std::pair<vec,matrix> gauss_markov(const matrix& m, const vec& y, const matrix& R_v);



#endif

