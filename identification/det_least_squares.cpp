#include "det_least_squares.h"

vec det_rlse::compute(const vec& m_new, rnum y_new)
{
    y_prev = y_new;
    if(full_rank){
        theta = theta + P*m_new*(1/(weight + m_new*P*m_new))*(y_new - m_new*theta);
        P = 1/weight*P - 1/weight*P*m_new*(1/(weight + m_new*P*m_new))*m_new*P;
        return theta;
    } else {
        matrix M_tild(M.rows()+1, M.cols());
        for(nnum i=0; i<M.rows(); i++)
            for(nnum j=0; j<M.cols(); j++)
                M_tild(i,j) = M(i,j);

        for(nnum i=0; i<M.cols(); i++)
            M_tild(M.rows(), i) = m_new[i];

        Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(M_tild);
        if(M_tild.rank() == M_tild.cols()){
            full_rank = true;
            P = (M_tild.transpose() * M_tild).inverse();
        }
        M = M_tild;
        vec y(M.rows());
        for(nnum i=0; i<y.len()-1; i++)
            y[i] = M(i+1,0);
        y[y.len()-1] = y_new;

        theta = project_vector_solution(M, y);
        return theta;
    }
}


vec det_rlse::compute(rnum y_new, rnum u_new)
{
    vec y(M.rows()+2);
    for(nnum i=0; i<y.len()-2; i++)
        y[i] = M(i,0);
    y[y.len()-2] = y_prev;
    y[y.len()-1] = y_new;

    vec u(M.rows()+1);
    for(nnum i=0; i<u.len()-1; i++)
        u[i] = M(i,0);
    u[u.len()-1] = u_new;

    vec m = compute_mline(y,u,order,causal);
    return compute(m, y_new);
}

vec compute_mline(const vec& y, const vec& u, nnum n, bool causal)
{
    if(causal){
        vec m_new(2*n);
        for(nnum i=0; i<n; i++){
            m_new[i] = y[y.len()-2-i];
            m_new[n+i] = u[u.len()-1-i];
        }
        return m_new;
    } else{
        vec m_new(2*n+1);
        for(nnum i=0; i<n; i++){
            m_new[i] = y[y.len()-2-i];
            m_new[n+i+1] = u[u.len()-2-i];
        }
        m_new[n+1] = u[u.len()-1];
        return m_new;
    }
}

matrix compute_m(const vec& y, const vec& u, nnum n, bool causal)
{
    if(causal){
        matrix m(y.len()-1, 2*n);
        for(nnum j=0; j<n; j++){
            for(nnum i=0; i<m.rows()-j; j++){
                m(j+i,j) = y[i];
                m(j+i,j+n) = u[i];
            }
        }
        return m;
    } else{
        matrix m(y.len(), 2*n+1);
        for(nnum j=0; j<n; j++){
            for(nnum i=0; i<m.rows()-1-j; j++){
                m(j+i+1,j) = y[i];
                m(j+i+1,j+n+1) = u[i];
            }
        }
        for(nnum i=0; i<m.rows(); i++){
            m(i,n) = u[i];
        }
        return m;
    }
}

vec project_vector(const matrix& m, const vec& v)
{
    return m*project_vector_solution(m,v);
}


//#define EXACT_PROJECTION
vec project_vector_solution(const matrix& m, const vec& v)
{
    Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(m);
    if(lu_decomp.rank() == m.cols()){
        return (m.transpose()*m).inverse() * m.transpose()*v;
    }
#ifdef EXACT_PROJECTION
    else{
        matrix N = Eigen::MatrixXd(lu_decomp.image(m));
        matrix P = Eigen::MatrixXd(lu_decomp.kernel());

        theta_zero = project_vector_solution(N,v);
        return (matrix::unit(m.cols()) - P*(P.transpose()*P).inverse()*P.transpose())*theta_zero;
    }
#else
#define PROJECTION_APPR_WEIGHT 0.01
    else{
        //matrix alpha_mat = PROJECTION_APPR_WEIGHT*matrix::unit(m.cols());
        matrix m_tild(m.rows()+m.cols(), m.cols());
        for(nnum i=0; i < m.cols(); i++)
            m_tild(i,i) = PROJECTION_APPR_WEIGHT;

        for(nnum i=0; i < m.rows(); i++)
            for(nnum j=0; j < m.cols(); j++)
                m_tild(i+m.cols(),j) = m(i,j);

        vec v_tild(m.cols()+m.rows());
        for(nnum i=0; i<m.rows(); i++)
            v_tild[m.cols() + i] = v[i];

        return project_vector_solution(m_tild, v_tild);
    }
#endif

}
