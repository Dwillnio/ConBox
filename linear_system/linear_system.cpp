 #include "linear_system.h"

vec linear_system::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    return A*x + B*u + E*z;
}

vec linear_system::y_val(const vec& x) const
{
    return C * x;
}

bool linear_system::SISO() const
{
    return d.dim_u == 1 && d.dim_w == 1;
}

bool linear_system::stable() const
{
    VectorXcd v = A.eigenvalues();
    for(nnum i = 0; i < v.size(); i++){
        if(v[i].real() >= 0)
            return false;
    }
    return true;
}


matrix linear_system::Q_B() const
{
    if(SISO()) {
        matrix m(A.rows(),A.cols());
        for(nnum i = 0; i < A.rows(); i++) {
            vec temp = C.row(0);
            for(nnum k = 0; k < i; k++)
                temp = temp * A;

            m = m.repl_row(i, temp);
        }

        return m;
    } else {
        matrix m(A.rows()*C.rows(),A.cols());
        for(nnum i = 0; i < A.rows(); i++) {
            matrix temp = C;
            for(nnum k = 0; k < i; k++)
                temp = temp * A;

            for(nnum j = 0; j < temp.rows(); j++){
                m = m.repl_row(i*C.rows()+j,temp.row(j));
            }
        }

        return m;
    }
}

matrix linear_system::T_B() const
{
    if(SISO()) {
        vec v(A.rows());
        matrix Q = Q_B().inverse();
        for(nnum i = 0; i < v.dimension(); i++)
            v[i] = Q(i,Q.cols()-1);

        matrix T(A.rows(), A.cols());
        for(nnum i = 0; i < T.cols(); i++) {
            vec temp(v);
            for(nnum k = 0; k < i; k++){
                temp = A * temp;
            }
            T = T.repl_col(i,temp);
        }

        return T;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::Q_S() const
{
    if(SISO()) {
        matrix m(A.rows(),A.cols());
        for(nnum i = 0; i < A.rows(); i++) {
            vec temp = B.col(0);

            for(nnum k = 0; k < i; k++){
                temp = A * temp;
            }

            m = m.repl_col(i,temp);
        }

        return m;
    } else {
        matrix m(A.rows(),A.cols() * B.cols());
        for(nnum i = 0; i < A.rows(); i++) {
            matrix temp = B;

            for(nnum k = 0; k < i; k++){
                temp = A * temp;
            }

            for(nnum j = 0; j < temp.cols(); j++){
                m = m.repl_col(i*B.cols()+j,temp.col(j));
            }
        }

        return m;
    }
}

matrix linear_system::T_S() const
{
    if(SISO()) {
        vec t(A.cols());
        matrix Q = Q_S().inverse();
        t = Q.row(Q.rows()-1);

        matrix T(A.rows(), A.cols());
        for(nnum i = 0; i < T.cols(); i++) {
            vec temp(t);
            for(nnum k = 0; k < i; k++){
                temp = temp * A;
            }
            T = T.repl_row(i, temp);
        }

        return T;
    } else {
        std::vector<nnum> ind = contr_ind();
        matrix test = Q_S_red();
        matrix qsrinv = Q_S_red().inverse();

        matrix t = t_S();
//        matrix t(B.cols(), A.cols());
//        nnum ind_sum = 0;
//        for(nnum i = 0; i < t.rows(); i++){
//            vec e(A.cols());
//            e[ind_sum + ind[i]] = 1;
//            ind_sum += ind[i];
//            t = t.repl_row(i, e * qsrinv);
//        }

        matrix T(A.rows(), A.cols());
        nnum sum = 0;
        for(nnum i = 0; i < ind.size(); i++){
            vec temp = t.row(i);
            for(nnum j = 0; j < ind[i]; j++){
                T = T.repl_row(sum + j, temp);
                temp = temp * A;
            }
            sum += ind[i];
        }

        return  T;
    }
}

#define OBSERVABLE_THRESHOLD 0.000001
bool linear_system::observable() const
{
    if(SISO()) {
        return std::abs(Q_B().det()) > OBSERVABLE_THRESHOLD;
    } else {
        return Q_B().rank() == A.rows();
    }
}

#define CONTROLLABLE_THRESHOLD 0.000001
bool linear_system::controllable() const
{
    if(SISO()) {
        return std::abs(Q_S().det()) > CONTROLLABLE_THRESHOLD;
    } else {
        return Q_S().rank() == A.rows();
    }
}

linear_system linear_system::control_normal_form() const
{
    if(SISO()) {
        if(controllable())
            return transform_inv(T_S());
        else
            throw new std::runtime_error("NOT CONTROLLABLE");
    } else {
        if(controllable())
            return transform_inv(T_S());
        else
            throw new std::runtime_error("NOT CONTROLLABLE");
    }
}

linear_system linear_system::observation_normal_form() const
{
    if(SISO()) {
        if(observable())
            return transform(T_B());
        else
            throw new std::runtime_error("NOT CONTROLLABLE");
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

//redo all with complex matrices
linear_system linear_system::diagonal_form() const
{
    Eigen::EigenSolver<MatrixXd> es(A);
    Eigen::MatrixXcd tr = es.eigenvectors();

    linear_system transformed(*this);
    transformed.A = (tr.inverse() * A.eigenrep() * tr).real();
    transformed.B = (tr.inverse() * B.eigenrep()).real();
    transformed.E = (tr.inverse() * E.eigenrep()).real();
    transformed.C = (C.eigenrep() * tr).real();

    return transformed;
}

linear_system linear_system::transform(const matrix& tr) const
{
    linear_system transformed(*this);
    transformed.A = tr.inverse() * A * tr;
    transformed.B = tr.inverse() * B;
    transformed.E = tr.inverse() * E;
    transformed.C = C * tr;

    return transformed;
}

linear_system linear_system::transform_inv(const matrix& tr) const
{
    linear_system transformed(*this);
    transformed.A = tr * A * tr.inverse();
    transformed.B = tr * B;
    transformed.E = tr * E;
    transformed.C = C * tr.inverse();

    return transformed;
}

VectorXcd linear_system::eigen_values() const
{
    return A.eigenvalues();
}

std::vector<VectorXcd> linear_system::eigen_vectors() const
{
    return A.eigenvectors();
}

matrix linear_system::H() const
{
    matrix qsrinv = Q_S_red().inverse();
    std::vector<nnum> ind = contr_ind();

    matrix matH(B.cols(), B.cols());

    matrix t(B.cols(), A.cols());
    nnum ind_sum = 0;
    for(nnum i = 0; i < t.cols(); i++){
        vec e(A.cols());
        e[ind_sum + ind[i]] = 1;
        ind_sum += ind[i];
        t = t.repl_row(i, e * qsrinv);
    }

    for(nnum i = 0; i < ind.size(); i++){
        matrix temp = matrix::unit(A.rows());
        for(nnum j = 0; j < i; j++){
            temp = temp * A;
        }
        matH = matH.repl_row(i, t.row(i) * temp);
    }

    return matH;
}

matrix linear_system::feedback_ackermann(const polynom& ch_p)  const
{
    if(SISO()){
        if(!controllable())
            return matrix(0,0);

        vec t_T = Q_S().inverse().row(A.rows()-1);

        matrix sum(t_T.dimension(), t_T.dimension());
        for(nnum i = 0; i < ch_p.deg_c(); i++){
            matrix A_k = matrix::unit(A.rows());
            for(nnum k = 0; k < i; k++)
                A_k *= A;

            sum += ch_p[i] * A_k;
        }
        matrix A_n = matrix::unit(A.rows());
        for(nnum k = 0; k < ch_p.deg_c(); k++)
            A_n *= A;

        sum += ch_p[ch_p.deg_c()] * A_n;

        vec k_T = t_T * sum;

        matrix K(k_T);

        return K.transpose();
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::feedback_ackermann(const std::vector<polynom>& pols) const
{
    if(SISO()){
        if(pols.size() == 0){
            throw new std::runtime_error("WRONG POLYNOM(ACKERMANN)");
        }
        return feedback_ackermann(pols[0]);
    } else {
        matrix qsrinv = Q_S_red().inverse();
        std::vector<nnum> ind = contr_ind();
        if(pols.size() != B.cols())
            throw new std::runtime_error("WRONG AMOUNT OF POLYNOMS(ACKERMANN)");

        for(nnum i = 0; i < ind.size(); i++){
            if(pols[i].deg_c() != ind[i])
                throw new std::runtime_error("WRONG POLYNOM DEGREE(ACKERMANN)");
        }

        matrix t = t_S();

        matrix temp(B.cols(), A.rows());
        for(nnum i = 0; i < B.cols(); i++){
            matrix sum(A.rows(), A.cols());
            for(nnum j = 0; j<=pols[i].deg_c(); j++){
                sum += pols[i][j] * A.power(j);
            }
            temp = temp.repl_row(i,t.row(i)*sum);
        }

        return H().inverse() * temp;
    }
}

matrix linear_system::feedback_decoupling(const polynom& ch_p)  const
{
    if(SISO()){
        auto p = H_y();
        if(ch_p.deg_c() != p.second[0])
            throw new std::runtime_error("CHAR POLYNOM WRONT DEG");

        rnum h = p.first(0,0);

        matrix sum(A.rows(), A.cols());
        for(nnum i = 0; i < ch_p.deg_c(); i++){
            matrix A_k = matrix::unit(A.rows());
            for(nnum k = 0; k < i; k++)
                A_k *= A;

            sum += ch_p[i] * A_k;
        }
        matrix A_n = matrix::unit(A.rows());
        for(nnum k = 0; k < ch_p.deg_c(); k++)
            A_n *= A;

        sum += ch_p[ch_p.deg_c()] * A_n;

        sum = 1/h * C * sum;

        return sum;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::feedback_decoupling(const std::vector<polynom>& pols) const
{
    if(SISO()){
        if(pols.size() == 0){
            throw new std::runtime_error("WRONG POLYNOM(FEEDBACK DECOUPLING)");
        }
        return feedback_decoupling(pols[0]);
    } else {
        std::pair<matrix, std::vector<nnum>> p = H_y();
        matrix hy = p.first;
        std::vector<nnum> ind = p.second;

        if((long)pols.size() != B.cols())
            throw new std::runtime_error("WRONG AMOUNT OF POLYNOMS(FEEDBACK DECOUPLING)");

        for(nnum i = 0; i < ind.size(); i++){
            if(pols[i].deg_c() != ind[i])
                throw new std::runtime_error("WRONG POLYNOM DEGREE(FEEDBACK DECOUPLING)");
        }

        matrix temp(C.rows(), A.cols());
        for(nnum i = 0; i < C.rows(); i++){
            matrix sum(A.rows(), A.cols());
            for(nnum j = 0; j<=pols[i].deg_c(); j++){
                sum += pols[i][j] * A.power(j);
            }
            temp = temp.repl_row(i,C.row(i)*sum);
        }

        return hy.inverse() * temp;
    }
}

std::pair<matrix, std::vector<nnum>> linear_system::H_y() const
{
    if(SISO()){
        nnum count = 0;
        matrix A_k = matrix::unit(A.rows());
        for(; count < A.rows(); count++){
            if(std::abs((C*A_k*B)(0,0)) > 0.00000001)
                break;
            A_k *= A;
        }
        std::vector<nnum> v;
        v.push_back(count+1);
        return std::pair<matrix, std::vector<nnum>>((C*A_k*B),v);

    } else {
        if(B.cols() != C.rows())
            throw new std::runtime_error("NUMBER OF INPUTS AND OUTPUTS NEED TO MATCH");

        matrix hy(C.rows(), B.cols());
        std::vector<nnum> ind;
        for(nnum i = 0; i < B.cols(); i++){
            nnum count = 0;
            matrix A_k = matrix::unit(A.rows());
            vec c = C.row(i);
            vec b = B.col(i);
            for(; count < A.rows(); count++){
                if(std::abs(c*A_k*b) > 0.00000001)
                    break;
                A_k *= A;
            }
            ind.push_back(count);
        }
        for(nnum i = 0; i < hy.rows(); i++){
            matrix Aexp = A.power(ind[i]-1);
            vec c = C.row(i);
            for(nnum j = 0; j < hy.cols(); j++){
                vec b = B.col(i);
                hy(i,j) = c * Aexp * b;
            }
        }

        return std::pair<matrix, std::vector<nnum>>(hy, ind);
    }
}

std::vector<nnum> linear_system::rel_deg() const
{
    return H_y().second;
}

std::vector<nnum> linear_system::contr_ind() const
{
    matrix qs = Q_S();

    std::vector<nnum> ind(B.cols(), UINT_MAX);
    nnum rank_prev = 0;
    for(nnum i = 0; i < qs.cols(); i++){
        matrix temp = qs.block(qs.rows(), i+1);
        nnum rank_cur = temp.rank();
        if(rank_prev == rank_cur && ind[i%B.cols()] == UINT_MAX){
            ind[i%B.cols()] = i/B.cols();
        }
        rank_prev = rank_cur;
    }

    return ind;
}


matrix linear_system::Q_S_red() const
{
    matrix qsred(A.rows(), A.cols());

    std::vector<nnum> ind = contr_ind();

    nnum sum = 0;
    for(nnum i = 0; i < ind.size(); i++){
        nnum index = ind[i];
        vec temp = B.col(i);
        for(nnum j = 0; j < index; j++){
            qsred = qsred.repl_col(sum + j, temp);
            temp = A * temp;
        }
        sum += index;
    }
//    for(nnum index: ind){
//        vec temp = B.col(index);
//        for(nnum j = 0; j < index; j++){
//            qsred.repl_col(sum + j, temp);
//            temp = A * temp;
//        }
//        sum += index;
//    }

    return qsred;
}

matrix linear_system::t_S() const
{
    matrix qsrinv = Q_S_red().inverse();
    std::vector<nnum> ind = contr_ind();

    matrix t(B.cols(), A.rows());
    nnum ind_sum = 0;
    for(nnum i = 0; i < t.rows(); i++){
        vec e(A.cols());
        e[ind_sum + ind[i]-1] = 1;
        ind_sum += ind[i];
        t = t.repl_row(i, e * qsrinv);
    }

    return t;
}

matrix linear_system::feedback_disturbance()  const
{
    return -1.0*(B.transpose() * B).inverse() * B.transpose() * E;
}

matrix linear_system::static_prefilter(const matrix& K)  const
{
    matrix m0 = B*K;
    matrix m1 = (m0 - A).inverse();
    matrix m2 = C*m1;
    matrix m3 = m2*B;
    matrix m4 = m3.inverse();
    return m4;
}


matrix linear_system::L(const polynom& ch_p) const
{
    if(SISO()){
        matrix sum(A.rows(), A.cols());
        matrix temp = matrix::unit(A.rows());
        for(nnum i = 0; i <= ch_p.deg_c(); i++){
            sum += ch_p[i] * temp;
            temp = temp * A;
        }
        matrix q = Q_B();
        q = q.inverse();
        vec t = Q_B().inverse().col(A.rows()-1);
        return matrix(sum * t);
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}































