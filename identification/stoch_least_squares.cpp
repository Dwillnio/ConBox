 #include "stoch_least_squares.h"

vec stoch_rlse::compute(const vec& m_new, rnum y_new, rnum r_v)
{
     vec K = (P*m_new)*(1/(m_new*P*m_new + r_v));
     theta = theta + K*(y_new - m_new*theta);

     matrix K_mat(K);
     matrix temp_mat(P*m_new);
     P = P - K_mat*temp_mat.transpose();

     return theta;
}

vec stoch_rlse::compute(rnum y_new, rnum u_new, rnum r_v)
{
    vec y(M.rows()+2);
    for(nnum i=0; i<y.dimension()-2; i++)
        y[i] = M(i,0);
    y[y.dimension()-2] = y_prev;
    y[y.dimension()-1] = y_new;

    vec u(M.rows()+1);
    for(nnum i=0; i<u.dimension()-1; i++)
        u[i] = M(i,0);
    u[u.dimension()-1] = u_new;

    vec m = compute_mline(y,u,order,causal);
    return compute(m, y_new, r_v);
}


std::pair<vec,matrix> most_likely_solution(const matrix& m, const vec& y,
                                           const matrix& R_th, const matrix& R_v, const matrix& R_thv)
{
    matrix K = (R_th*m.transpose() + R_thv)*(m*R_th*m.transpose() + m*R_thv + R_thv.transpose()*m.transpose() + R_v).inverse();
    matrix P = R_th - K*(m*R_th + R_thv);
    vec theta = K*y;
    return std::pair<vec,matrix>(theta,P);
}

std::pair<vec,matrix> most_likely_solution(const matrix& m, const vec& y,
                                           const matrix& R_th, const matrix& R_v)
{
    matrix P = (R_th.inverse() + m.transpose()*R_v.inverse()*m).inverse();
    vec theta = P*m.transpose()*R_v.inverse()*y;
    return std::pair<vec,matrix>(theta,P);
}

std::pair<vec,matrix> gauss_markov(const matrix& m, const vec& y, const matrix& R_v)
{
    matrix P = (m.transpose()*R_v.inverse()*m).inverse();
    vec theta = P*m.transpose()*R_v.inverse()*y;
    return std::pair<vec,matrix>(theta,P);
}

