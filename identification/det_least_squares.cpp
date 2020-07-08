#include "det_least_squares.h"

vec project_vector(const matrix& m, const vec& v)
{
    return m*project_vector_solution(m,v);
}


//#define EXACT_PROJECTION
vec project_vector_solution(const matrix& m, const vec& v)
{
    Eigen::FullPivLU<Eigen::Matrix3f> lu_decomp(m);
    if(lu_decomp.rank() == m.cols()){
        return (m.transpose()*m).inverse() * m.transpose()*v;
    }
#ifdef EXACT_PROJECTION
    else{
        matrix N = Eigen::MatrixXd(lu_decomp.image(m));
        matrix P = Eigen::MatrixXd(lu_decomp.kernel());
        //TODO implement
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
                m_tild(i,j) = m(i,j);



        vec v_tild(m.cols()+m.rows());
        for(nnum i=0; i<m.rows(); i++)
            v_tild[m.cols() + i] = v[i];

        return project_vector_solution(m_tild, v_tild);
    }
#endif

}
