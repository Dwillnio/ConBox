#ifndef DET_LEAST_SQUARES
#define DET_LEAST_SQUARES

#include "base/vec.h"
#include "base/matrix.h"

//deterministic recursive least squares estimator
class det_rlse
{
public:
    det_rlse(const matrix& M0_, const vec& theta0_, nnum order_, bool causal_ = 1, rnum weight_ = 1)
        : order(order_), causal(causal_), weight(weight_), P(M0_.cols(), M0_.cols()), M(M0_), y_prev(0), theta(theta0_)
    {
        Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(M0_);
        if(M.rank() == M.cols()){
            P = (M.transpose() * M).inverse();
            full_rank = true;
        } else {
            full_rank = false;
        }
    }

    vec compute(const vec& m_new, rnum y_new);
    vec compute(rnum y_new, rnum u_new);

protected:
    nnum order;
    bool full_rank, causal;
    rnum weight;
    matrix P, M;
    rnum y_prev;
    vec theta;
};

//  projects vector v onto subspace defined by img m
//  return projection
vec project_vector(const matrix& m, const vec& v);

//  projects vector v onto subspace defined by img m
//  returns necessary vector x, m*x = projection
vec project_vector_solution(const matrix& m, const vec& v);

//  computes the last line of the m matrix for a discrete system of order n
vec compute_mline(const vec& y, const vec& u, nnum n, bool causal = true);

//  computes the m matrix for a discrete sytem of order n
matrix compute_m(const vec& y, const vec& u, nnum n, bool causal = true);

#endif
