 #include "linear_system.h"

vec value(const vec& x, const vec& u, const vec& z);
vec y_val(const vec& x);

bool linear_system::SISO() const
{
    return d.dim_u == 1 && d.dim_w == 1;
}

bool linear_system::stable() const
{
    vec v = A.eigenvalues();
    for(nnum i = 0; i < v.dimension(); i++){
        if(v[i]>=0)
            return false;
    }
    return true;
}


matrix linear_system::Q_B() const
{
    if(SISO()) {
        matrix m(A.d_row(),A.d_col());
        for(nnum i = 0; i < A.d_row(); i++) {
            vec temp = C[0];
            for(nnum k = 0; k < i; k++)
                temp * A;

            m[i] = temp.get();
        }
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::T_B() const
{
    if(SISO()) {
        vec v(A.d_row());
        matrix Q = Q_B().inverse();
        for(nnum i = 0; i < v.dimension(); i++)
            v[i] = Q[i][Q.d_col()-1];

        matrix T(A.d_row(), A.d_col());
        for(nnum i = 0; i < T.d_col(); i++) {
            vec temp(v);
            for(nnum k = 0; k < i; k++){
                temp = A * temp;
            }
            T.repl_col(i,temp);
        }
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::Q_S() const
{
    if(SISO()) {
        matrix m(A.d_row(),A.d_col());
        for(nnum i = 0; i < A.d_row(); i++) {
            vec temp = B.to_vec();

            for(nnum k = 0; k < i; k++){
                temp = B * temp;
            }

            m.repl_col(i,temp);
        }
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

matrix linear_system::T_S() const
{
    if(SISO()) {
        vec t(A.d_col());
        matrix Q = Q_S().inverse();
        t = Q[Q.d_row()-1];

        matrix T(A.d_row(), A.d_col());
        for(nnum i = 0; i < T.d_col(); i++) {
            vec temp(t);
            for(nnum k = 0; k < i; k++){
                temp = temp * A;
            }
            T[i] = temp.get();
        }
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

#define OBSERVABLE_THRESHOLD 0.0001
bool linear_system::observable() const
{
    if(SISO()) {
        return std::abs(Q_B().det()) > OBSERVABLE_THRESHOLD;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

#define CONTROLLABLE_THRESHOLD 0.0001
bool linear_system::controllable() const
{
    if(SISO()) {
        return std::abs(Q_S().det()) > OBSERVABLE_THRESHOLD;
    } else {
        throw new std::runtime_error("NOT IMPLEMENTED FOR MIMO");
    }
}

linear_system linear_system::control_normal_form() const
{

}

linear_system linear_system::observation_normal_form() const
{

}

linear_system linear_system::diagonal_form() const
{

}

linear_system linear_system::transform(const matrix& tr) const
{

}

vec linear_system::eigen_values() const
{

}

std::vector<vec> linear_system::eigen_vectors() const
{

}


matrix linear_system::feedback_ackermann(vec eigenvalues)  const
{

}

matrix linear_system::feedback_decoupling(vec eigenvalues)  const
{

}

matrix linear_system::feedback_disturbance()  const
{

}

