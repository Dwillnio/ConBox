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
