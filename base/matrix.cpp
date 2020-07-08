#include "matrix.h"


matrix matrix::operator* (rnum d) const
{
   matrix m(*this);
   m *= d;
   return m;
}

matrix& matrix::operator*= (rnum d)
{
    for(nnum i=0; i<rows(); i++){
        for(nnum j=0; j<cols(); j++) {
            (*this)(i,j) *= d;
        }
    }

    return *this;
}


matrix matrix::operator* (int d) const
{
    return (double)d * *this;
}

matrix& matrix::operator*= (int d)
{
    *this *= (double)d;
    return *this;
}

matrix operator* (int d, const matrix& m)
{
    return m * d;
}

matrix matrix::operator* (nnum d) const
{
    return (double)d * *this;
}

matrix& matrix::operator*= (nnum d)
{
    *this *= (double)d;
    return *this;
}

matrix operator* (nnum d, const matrix& m)
{
    return m * d;
}

matrix matrix::power(nnum i) const
{
    if(cols() != rows())
        throw new std::runtime_error("MATRIX NOT SQUARE(POW)");

    matrix ret = matrix::unit(this->rows());
    for(nnum j = 0; j < i; j++)
        ret = ret * (*this);

    return ret;
}

nnum factorial(nnum n)
{
    if(n == 1 || n == 0)
        return 1;
    return n*factorial(n-1);
}

matrix matrix::exp(nnum cutoff) const
{
    if(cols() != rows())
        throw new std::runtime_error("MATRIX NOT SQUARE(EXP)");

    matrix temp(rows(),cols());
    for(; cutoff >=0 ; cutoff--){
        temp = temp * (*this);
        temp += (1/factorial(cutoff)) * matrix::unit(rows());
    }

    return temp;
}

matrix matrix::log(nnum cutoff) const
{
    if(cols() != rows())
        throw new std::runtime_error("MATRIX NOT SQUARE(EXP)");

    matrix R = (matrix::unit(rows()) - *this) * (*this + matrix::unit(rows())).inverse();

    matrix sum(rows(), cols());
    for(nnum i = 1; i <= cutoff; i++){
        sum += 1/(2*i + 1) * R.power(2*i + 1);
    }

    return -2 * sum;
}


matrix matrix::operator* (const matrix& m) const
{
    if(cols() != m.rows())
        throw new std::runtime_error("MATRIX DIM MISMATCH");

    matrix w(rows(), m.cols());
    for(nnum i=0; i<w.rows(); i++){
        for(nnum j=0; j<w.cols(); j++) {
            w(i,j) = 0;
            for(nnum k=0; k<cols(); k++){
                w(i,j) += (*this)(i,k) * m(k,j);
            }
        }
    }

    return w;
}

matrix& matrix::operator*= (const matrix& m)
{
    *this = *this * m;
    return *this;
}


vec matrix::operator* (const vec& v) const
{
    if(cols() != v.dimension())
        throw new std::runtime_error("MATRIX VECTOR DIM MISMATCH");

    vec u(this->rows());

    for(nnum i=0; i<rows(); i++){
        u[i] = 0;
        for(nnum j=0; j<cols(); j++) {
            u[i] += (*this)(i,j) * v[j];
        }
    }

    return u;
}


matrix matrix::operator+ (const matrix& m) const
{
    matrix w = *this;
    w += m;
    return w;
}

matrix& matrix::operator+= (const matrix& m)
{
    for(nnum i=0; i<rows(); i++){
        for(nnum j=0; j<cols(); j++) {
            (*this)(i,j) += m(i,j);
        }
    }

    return *this;
}

matrix matrix::operator- (const matrix& m) const
{
    matrix w = *this;
    w -= m;
    return w;
}

matrix& matrix::operator-= (const matrix& m)
{
    for(nnum i=0; i<rows(); i++){
        for(nnum j=0; j<cols(); j++) {
            (*this)(i,j) -= m(i,j);
        }
    }

    return *this;
}


matrix operator* (rnum d, const matrix& m)
{
    return m*d;
}


vec operator* (const vec& v, const matrix& m)
{
    if(m.rows() != v.dimension())
        throw new std::runtime_error("MATRIX VECTOR DIM MISMATCH");

    vec u(m.cols());

    for(nnum j=0; j<m.cols(); j++) {
        u[j] = 0;
        for(nnum i=0; i<m.rows(); i++){
            u[j] += m(i,j) * v[i];
        }
    }

    return u;
}


std::ostream& operator<<(std::ostream &os, const matrix& m)
{
    for(nnum i=0; i<m.rows(); i++){
        os << "| ";
        for(nnum j=0; j<m.cols(); j++) {
            os << m(i,j);
            os << " ";
        }
        os << "|";
        os << "\r\n";
    }

    return os;
}

matrix matrix::unit(nnum d)
{
    matrix m(d,d);
    for(nnum i=0; i<d; i++) {
        m(i,i) = 1;
    }
    return m;
}

matrix matrix::zero(nnum d)
{
    return MatrixXd(d,d);
}

matrix matrix::block(nnum offset_rows, nnum offset_cols, nnum r, nnum c) const
{
    if(r+offset_rows > rows() || c + offset_cols > cols())
        throw new std::runtime_error("MATRIX BLOCK OUT OF BOUNDS");

    matrix m(r, c);
    for(nnum i = 0; i < r; i++){
        for(nnum j = 0; j < c; j++){
            m(i,j) = (*this)(i+offset_rows, j+offset_cols);
        }
    }

    return m;
}

matrix matrix::repl_row(nnum r, vec v) const
{
    if(cols() != v.dimension())
        throw new std::runtime_error("RREPL MATRIX VECTOR DIM MISMATCH");

    matrix m(*this);
    for(nnum i = 0; i < cols(); i++)
        m(r,i) = v[i];

    return m;
}

matrix matrix::repl_col(nnum c, vec v) const
{
    if(rows() != v.dimension())
        throw new std::runtime_error("CREPL MATRIX VECTOR DIM MISMATCH");

    matrix m(*this);
    for(nnum i = 0; i < rows(); i++)
        m(i,c) = v[i];

    return m;
}


vec matrix::col(nnum c) const
{
    if(c >= cols())
        throw new std::runtime_error("MATRIX COL DIM MISMATCH");

    vec v(rows());
    for(nnum i = 0; i < rows(); i++){
        v[i] = (*this)(i,c);
    }
    return v;
}

vec matrix::row(nnum r) const
{
    if(r >= rows())
        throw new std::runtime_error("MATRIX ROW DIM MISMATCH");

    vec v(cols());
    for(nnum i = 0; i < cols(); i++){
        v[i] = (*this)(r,i);
    }
    return v;
}

matrix matrix::del(nnum row, nnum col) const
{
    matrix m(rows()-1, cols()-1);

    for(nnum i=0; i<rows(); i++) {
        for(nnum j=0; j<cols(); j++) {
            nnum i_new = i;
            nnum j_new = j;

            if(i == row || j == col) continue;
            if(i > row) i_new--;
            if(j > col) j_new--;


            m(i_new,j_new) = (*this)(i,j);
        }
    }

    return m;
}

matrix matrix::transpose() const
{
    matrix m(cols(), rows());
    for(nnum i=0; i<rows(); i++) {
        for(nnum j=0; j<cols(); j++) {
            m(j,i) = (*this)(i,j);
        }
    }
    return m;
}

rnum matrix::det() const
{
    if(rows() != cols())
        throw new std::runtime_error("DET NOT SQUARE");

    if(rows() == 1)
        return (*this)(0,0);

    rnum sum = 0;

    for(nnum i=0; i < cols(); i++) {
        matrix m = this->del(0,i);
        if((*this)(0,i))
            sum += (i%2?-1:1) * (*this)(0,i) * m.det();
    }

    return sum;
}

matrix matrix::adj() const
{
    if(cols() == 1 && rows() == 1)
        return matrix::unit(1);
    matrix m(cols(), rows());
    matrix temp(*this);
    for(nnum i=0; i<rows(); i++) {
        for(nnum j=0; j<cols(); j++) {
            m(i,j) = std::pow(-1, i+j) * temp.del(i,j).det();
        }
    }
    return m.transpose();
}

matrix matrix::inverse() const
{
    rnum det = this->det();
    if(!det)
        throw new std::runtime_error("MATRIX NOT INVERTIBLE");

    matrix m = this->adj();

    return (1/det)*m;
}

nnum matrix::rank() const
{

    Eigen::FullPivLU<MatrixXd> lu_decomp(*this);
    return lu_decomp.rank();
}

nnum matrix::kerneldim() const
{
    Eigen::FullPivLU<MatrixXd> lu_decomp(*this);
    return lu_decomp.dimensionOfKernel();
}

std::pair<matrix, matrix> matrix::QR_decomposition() const
{
    if(cols() != rows())
        throw new std::runtime_error("QRDECOMP MATRIX NOT SQUARE");

    matrix U(rows(), cols());
    matrix A_T(this->transpose());

    for(nnum i = 0; i<rows(); i++){
        vec a(A_T.row(i));
        vec u(a);

        for(nnum k = 0; k<i; k++){
            vec u_k = vec(U.row(k));
            vec proj = (u_k * a) / (u_k * u_k) * u_k;
            u += -1 * proj;
        }

        for(nnum j = 0; j<rows(); j++){
            U(i,j) = u[j];
        }
    }

    matrix Q(U);

    for(nnum i = 0; i<rows(); i++){
        vec u(Q.row(i));
        rnum len = u.len();

        for(nnum j = 0; j<rows(); j++){
            Q(i,j) /= len;
        }
    }

    matrix R(rows(), cols());

    for(nnum j = 0; j<cols(); j++){
        for(nnum i = 0; i<=j; i++){
            R(i,j) = vec(Q.row(i)) * vec(A_T.row(j));
        }
    }

    U = U.transpose();
    Q = Q.transpose();

    return std::pair<matrix,matrix>(Q,R);
}


VectorXcd matrix::eigenvalues() const
{
    VectorXcd v = MatrixXd::eigenvalues();

    return v;
}

rnum matrix::max_eigenvalue() const
{
    vec max_ev = max_eigenvector();
    vec pr = (*this) * max_ev;

    nnum index = 0;
    for(; index <= pr.dimension(); index++){
        if(index == pr.dimension())
            break;

        if(max_ev[index] != 0)
            break;
    }
    if(index == pr.dimension()) //error message?
        return 0;

    return pr[index] / max_ev[index];
}

std::vector<Eigen::VectorXcd> matrix::eigenvectors() const
{
    Eigen::EigenSolver<MatrixXd> es(*this);

    std::vector<Eigen::VectorXcd> v(es.eigenvectors().cols());
    for(nnum i = 0; i < v.size(); i++){
        v[i] = es.eigenvectors().col(i);
    }

    return v;
}

#define EV_INVIT_ITERATIONS 10
#define EV_INVIT_OFFSET 0.01
vec matrix::eigenvector_to(rnum eigenvalue) const
{
    if(cols() != rows())
        throw new std::runtime_error("MAX EV CALC MATRIX NOT SQUARE");

    vec v(rows());
    v[0] = 1;
    if(rows() > 1)
        v[1] = std::sqrt(M_PI);

    matrix m(((*this) - ((eigenvalue-EV_INVIT_OFFSET)*matrix::unit(rows()))).inverse());

    for(nnum i = 0; i<EV_INVIT_ITERATIONS; i++) {
        vec temp = m*v;
        v = temp*(1/temp.len());
    }

    return v;
}

#define EV_POWER_ITERATIONS 20
vec matrix::max_eigenvector() const
{
    if(cols() != rows())
        throw new std::runtime_error("MAX EV CALC MATRIX NOT SQUARE");

    vec v(rows());
    v[0] = 1;
    if(rows() > 1)
        v[1] = std::sqrt(M_PI);

    for(nnum i = 0; i<EV_POWER_ITERATIONS; i++) {
        vec temp = (*this)*v;
        v = temp*(1/temp.len());
    }

    return v;
}
















