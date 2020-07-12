#include "linear_system_d.h"

vec linear_system_d::value(nnum k, const vec& x, const vec& u, const vec& z)
{
    return A*x + B*u + E*z;
}

vec linear_system_d::y_val(const vec& x) const
{
    return C*x;
}

#define INTEGRATION_STEPS 1000
linear_system_d linear_system_d::convert(const linear_system& sys, rnum dt)
{
    matrix A_d = Eigen::MatrixXd((dt*sys.A_mat()).exp());

    matrix accumulation(sys.A_mat().rows(), sys.A_mat().cols());
    rnum h = dt/(INTEGRATION_STEPS+1);
    rnum alpha = 0;
    matrix m1 = Eigen::MatrixXd((alpha*sys.A_mat()).exp());
    matrix m2 = Eigen::MatrixXd(((alpha+h)*sys.A_mat()).exp());
    for(nnum i=0; i<INTEGRATION_STEPS-1; i++){
        accumulation += h/2 * (m1 + m2);
        alpha+=h;
        m1 = m2;
        m2 = Eigen::MatrixXd(((alpha+h)*sys.A_mat()).exp());
    }

    matrix B_d = accumulation * sys.B_mat();

    return linear_system_d(A_d, B_d, sys.C_mat());
}


matrix linear_system_d::convert_noise(const matrix& A, const matrix& Q, rnum dt)
{
    matrix accumulation(A.rows(), A.cols());

    rnum h = dt/(INTEGRATION_STEPS+1);

    matrix phi1 = Eigen::MatrixXd((A*(dt-0*h)).exp());
    matrix m1 = phi1*Q*phi1.transpose();
    matrix phi2 = Eigen::MatrixXd((A*(dt-(1)*h)).exp());
    matrix m2 =  phi2*Q*phi2.transpose();
    for(nnum i=0; i<INTEGRATION_STEPS-1; i++){
        accumulation += h/2 * (m1 + m2);
        m1 = m2;
        phi2 = Eigen::MatrixXd((A*(dt-(i+1)*h)).exp());
        m2 = phi2*Q*phi2.transpose();
    }

    return accumulation;
}
