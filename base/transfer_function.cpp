#include "transfer_function.h"


linear_system transfer_function::cnf(const polynom& y_coeffs_, const polynom& u_coeffs_)
{
    polynom y_coeffs(y_coeffs_), u_coeffs(u_coeffs_);
    nnum order = y_coeffs.deg();
    matrix A(order,order);

    for(nnum i=0; i<A.rows()-1; i++)
        A(i,i+1) = 1;

    for(nnum i=0; i<A.rows(); i++)
        A(A.rows()-1,i) = -y_coeffs[i];

    matrix B(order,1);
    B(B.rows()-1,0) = 1;

    matrix C(1,order);
    for(nnum i=0; i<u_coeffs.deg()+1; i++)
        C(0,i) = u_coeffs[i];

    return linear_system(A,B,C);
}

//linear_system transfer_function::cnf()
//{
//    nnum order = y_coeffs.deg();
//    matrix A(order,order);

//    for(nnum i=0; i<A.rows()-1; i++)
//        A(i,i+1) = 1;

//    for(nnum i=0; i<A.rows(); i++)
//        A(A.rows()-1,i) = -y_coeffs[i];

//    matrix B(order,1);
//    B(B.rows()-1,0) = 1;

//    matrix C(1,order);
//    for(nnum i=0; i<u_coeffs.deg()+1; i++)
//        C(0,i) = u_coeffs[i];

//    return linear_system(A,B,C);
//}


rnum transfer_function::step(const vec& u){
    x_vals = dgl_solver.step(t,x_vals,u,vec(0));
    t+=dt;
    return (lin_form.C_mat()*x_vals)[0];
}

vec transfer_function::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    return lin_form.value(t,x,u,z);
}

std::ostream& operator<< (std::ostream& os, const transfer_function& tf)
{
    os << "(";
    os << " " << tf.u_coeffs[0];
    for(nnum i=1; i<=tf.u_coeffs.deg_c(); i++){
        os << " + " << tf.u_coeffs[i] << "*" << "s^" << i;
    }
    os << " ) / (";
    os << " " << tf.y_coeffs[0];
    for(nnum i=1; i<=tf.y_coeffs.deg_c(); i++){
        os << " + " << tf.y_coeffs[i] << "*" << "s^" << i;
    }
    os << " )";
}




















