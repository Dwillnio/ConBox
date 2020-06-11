#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

#include <vector>

#include "base/vec.h"
#include "base/matrix.h"
#include "base/polynom.h"
#include "base/func_dgl.h"
#include "controller/dimensions.h"

class linear_system : public func_dgl
{
public:
    linear_system(const matrix& A_, const matrix& B_, const matrix& C_)
        : linear_system(A_, B_, C_, matrix(A_.rows(), 0)) {}

    linear_system(const matrix& A_, const matrix& B_, const matrix& C_, const matrix& E_)
        : func_dgl(A_.rows(), B_.cols(), E_.cols()), A(A_), B(B_), C(C_), E(E_)
    {
        d.dim_x = A.rows();
        d.dim_w = C.rows();
        d.dim_u = B.cols();
        d.dim_z = E.cols();

        if(A_.cols() != A_.rows() || A.cols() != d.dim_x)
            throw new std::runtime_error("LINSYSTEM A DIM ERROR");

        if(B_.rows() != d.dim_x || B.cols() != d.dim_u)
            throw new std::runtime_error("LINSYSTEM B DIM ERROR");

        if(C.rows() != d.dim_w || C_.cols() != d.dim_x)
            throw new std::runtime_error("LINSYSTEM C DIM ERROR");

        if(E.rows() != d.dim_x || E_.cols() != d.dim_z)
            throw new std::runtime_error("LINSYSTEM E DIM ERROR");
    }

    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z);
    vec y_val(const vec& x) const;

    bool SISO() const;
    bool stable() const;
    bool observable() const;
    bool controllable() const;
    linear_system control_normal_form() const;
    linear_system observation_normal_form() const;
    linear_system diagonal_form() const;
    linear_system transform(const matrix& tr) const;
    linear_system transform_inv(const matrix& tr) const;
    VectorXcd eigen_values() const;
    std::vector<VectorXcd> eigen_vectors() const;

    matrix feedback_ackermann(const polynom& ch_p) const;
    matrix feedback_ackermann(const std::vector<polynom>& pols) const;
    matrix feedback_decoupling(const polynom& ch_p) const;
    matrix feedback_decoupling(const std::vector<polynom>& pols) const;
    matrix feedback_disturbance() const;
    matrix static_prefilter(const matrix& K) const;

    linear_system feedback_system(const matrix& K) const;
    linear_system feedback_system(const matrix& K, const matrix& B_new) const;

    const matrix& A_mat() const {return A;}
    const matrix& B_mat() const {return B;}
    const matrix& C_mat() const {return C;}
    const matrix& E_mat() const {return E;}

    matrix Q_B() const;
    matrix T_B() const;
    matrix Q_S() const;
    matrix T_S() const;

    matrix t_S() const;
    matrix Q_S_red() const;
    matrix H() const;

    matrix L(const polynom& ch_p) const;

    std::pair<matrix, std::vector<nnum>> H_y() const;
    std::vector<nnum> rel_deg() const;
    std::vector<nnum> contr_ind() const;

protected:
    matrix A, B, C, E;
    dimensions d;
};

#endif
