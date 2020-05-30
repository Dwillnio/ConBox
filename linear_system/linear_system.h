#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

#include <vector>

#include "base/vec.h"
#include "base/matrix.h"
#include "controller/dimensions.h"

class linear_system
{
public:
    linear_system(const matrix& A_, const matrix& B_, const matrix& C_, const matrix& E_)
        : A(A_), B(B_), C(C_), E(E_)
    {
        d.dim_x = A.d_row();
        d.dim_w = C.d_row();
        d.dim_u = B.d_col();
        d.dim_z = E.d_col();

        if(A_.d_col() != A_.d_row() || A.d_col() != d.dim_x)
            throw new std::runtime_error("LINSYSTEM A DIM ERROR");

        if(B_.d_row() != d.dim_x || B.d_col() != d.dim_u)
            throw new std::runtime_error("LINSYSTEM B DIM ERROR");

        if(C.d_row() != d.dim_w || C_.d_col() != d.dim_x)
            throw new std::runtime_error("LINSYSTEM C DIM ERROR");

        if(E.d_row() != d.dim_x || E_.d_col() != d.dim_z)
            throw new std::runtime_error("LINSYSTEM E DIM ERROR");
    }

    vec value(const vec& x, const vec& u, const vec& z) const;
    vec y_val(const vec& x) const;

    bool SISO() const;
    bool stable() const;
    bool observable() const;
    bool controllable() const;
    linear_system control_normal_form() const;
    linear_system observation_normal_form() const;
    linear_system diagonal_form() const;
    linear_system transform(const matrix& tr) const;
    vec eigen_values() const;
    std::vector<vec> eigen_vectors() const;

    matrix feedback_ackermann(vec eigenvalues) const;
    matrix feedback_decoupling(vec eigenvalues) const;
    matrix feedback_disturbance() const;

    matrix Q_B() const;
    matrix T_B() const;
    matrix Q_S() const;
    matrix T_S() const;

protected:
    matrix A, B, C, E;
    dimensions d;
};

#endif
