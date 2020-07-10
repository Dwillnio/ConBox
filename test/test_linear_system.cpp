#include "test_linear_system.h"

void linear_system_test_1(std::ostream& os)
{
    linear_system ls = pendel_wagen_lin();

    os << "SISO: " << ls.SISO() << "\n";
    os << "Stable: " << ls.stable() << "\n";
    os << "Eigenvalues:\n" << ls.eigen_values() << "\n";
    os << "Observable: " << ls.observable() << "\n";
    os << ls.Q_B() << "\n";
    os << "Controllable: " << ls.controllable() << "\n";
    os << ls.Q_S() << "\n";
    os << "Control normal form:\n";
    linear_system cnf = ls.control_normal_form();
    os << cnf.A_mat() << cnf.B_mat();
    os << "\nFeedbackmatrix Ackermann EV 2x -1:\n";
    matrix K = ls.feedback_ackermann(polynom({1,4,6,4,1}));
    os << K;
}

void linear_system_test_2(std::ostream& os)
{
    linear_system ls = harm_osc();

    os << "SISO: " << ls.SISO() << "\n";
    os << "Stable: " << ls.stable() << "\n";
    os << "Eigenvalues:\n" << ls.eigen_values() << "\n";
    os << "Observable: " << ls.observable() << "\n";
    os << ls.Q_B() << "\n";
    os << "Controllable: " << ls.controllable() << "\n";
    os << ls.Q_S() << "\n";
    os << "Control normal form:\n";
    linear_system cnf = ls.control_normal_form();
    os << cnf.A_mat() << cnf.B_mat();
    os << "\nFeedbackmatrix Ackermann EV 2x -1:\n";
    matrix K = ls.feedback_ackermann(polynom({1,2,1}));
    os << K;
    os << "\nStatic prefilter:\n";
    matrix S = ls.static_prefilter(K);
    os << S;
}


void linear_system_test_3(std::ostream& os)
{
    matrix A({0,3,2, 1,0,4, 0,1,0}, 3), B({0,1,2, 0,0,1, 1,0,0}, 3), C(matrix::unit(3));
    linear_system exampl(A,B,C);
    auto cind = exampl.contr_ind();
    for(nnum i: cind)
        os << i << " , ";
    os << std::endl;

    matrix A2({0,0,1,0, 1,0,2,0, 0,1,3,1, 0,0,-1,2}, 4), B2({1,0, 0,0, 0,0, 0,1}, 4), C2({1,0,0,0},1);
    linear_system exampl2(A2,B2,C2);
    auto cind2 = exampl2.contr_ind();
    for(nnum i: cind2)
        os << i << " , ";
    os << std::endl;
    os << exampl2.control_normal_form().A_mat() << std::endl;
    os << exampl2.control_normal_form().B_mat() << std::endl;
    os << exampl2.control_normal_form().C_mat() << std::endl;
}
