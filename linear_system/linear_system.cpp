 #include "linear_system.h"

vec linear_system::value(rnum t, const vec& x, const vec& u, const vec& z) const
{
    if(z.dimension())

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
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
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
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
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
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

#define OBSERVABLE_THRESHOLD 0.000001
bool linear_system::observable() const
{
    if(SISO()) {
        return std::abs(Q_B().det()) > OBSERVABLE_THRESHOLD;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

#define CONTROLLABLE_THRESHOLD 0.000001
bool linear_system::controllable() const
{
    if(SISO()) {
        return std::abs(Q_S().det()) > CONTROLLABLE_THRESHOLD;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
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
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
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
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

std::vector<nnum> linear_system::rel_deg() const
{
    return H_y().second;
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































