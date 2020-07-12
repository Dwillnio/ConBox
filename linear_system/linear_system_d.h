#ifndef LINEAR_SYSTEM_D_H
#define LINEAR_SYSTEM_D_H

#include "base/matrix.h"
#include "controller/dimensions.h"
#include "base/func_d_dgl.h"
#include "linear_system.h"

class linear_system_d : public func_d_dgl
{
public:
    linear_system_d(const matrix& A_, const matrix& B_, const matrix& C_)
        : linear_system_d(A_, B_, C_, matrix(A_.rows(),0)){}

    linear_system_d(const linear_system& sys_);

    linear_system_d(const matrix& A_, const matrix& B_, const matrix& C_, const matrix& E_)
        : func_d_dgl(A_.rows(), B_.cols(), E_.cols()), A(A_), B(B_), C(C_), E(E_)
    {
        d.dim_x = A.rows();
        d.dim_w = C.rows();
        d.dim_u = B.cols();
        d.dim_z = E.cols();

        if(A_.cols() != A_.rows() || A.cols() != d.dim_x)
            throw new std::runtime_error("DLINSYSTEM A DIM ERROR");

        if(B_.rows() != d.dim_x || B.cols() != d.dim_u)
            throw new std::runtime_error("DLINSYSTEM B DIM ERROR");

        if(C.rows() != d.dim_w || C_.cols() != d.dim_x)
            throw new std::runtime_error("DLINSYSTEM C DIM ERROR");

        if(E.rows() != d.dim_x || E_.cols() != d.dim_z)
            throw new std::runtime_error("DLINSYSTEM E DIM ERROR");
    }

    virtual vec value(nnum k, const vec& x, const vec& u, const vec& z);
    vec y_val(const vec& x) const;

    const dimensions& dims() const {return d;}

    const matrix& A_mat() const {return A;}
    const matrix& B_mat() const {return B;}
    const matrix& C_mat() const {return C;}
    const matrix& E_mat() const {return E;}

    static linear_system_d convert(const linear_system& sys, rnum dt);
    static matrix convert_noise(const matrix& A, const matrix& Q, rnum dt);

protected:
    matrix A, B, C, E;
    dimensions d;
};

#endif // LINEAR_SYSTEM_D_H
