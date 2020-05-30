#include "matrix.h"

matrix matrix::operator* (rnum d) const
{
   matrix m(*this);
   m *= d;
   return m;
}

matrix& matrix::operator*= (rnum d)
{
    for(nnum i=0; i<dim_row; i++){
        for(nnum j=0; j<dim_col; j++) {
            (*this)[i][j] *= d;
        }
    }

    return *this;
}

matrix matrix::operator* (const matrix& m) const
{
    if(dim_col != m.dim_row)
        throw new std::runtime_error("MATRIX DIM MISMATCH");

    matrix w(dim_row, m.dim_col);
    for(nnum i=0; i<w.dim_row; i++){
        for(nnum j=0; j<w.dim_col; j++) {
            for(nnum k=0; k<dim_row; k++){
                w[i][j] += (*this)[i][k] * m[k][j];
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
    if(dim_col != v.dimension())
        throw new std::runtime_error("MATRIX VECTOR DIM MISMATCH");

    vec u(v.dimension());

    for(nnum i=0; i<dim_row; i++){
        u[i] = 0;
        for(nnum j=0; j<dim_col; j++) {
            u[i] += (*this)[i][j] * v[j];
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
    for(nnum i=0; i<dim_row; i++){
        for(nnum j=0; j<dim_col; j++) {
            (*this)[i][j] += m[i][j];
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
    for(nnum i=0; i<dim_row; i++){
        for(nnum j=0; j<dim_col; j++) {
            (*this)[i][j] -= m[i][j];
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
    if(m.d_row() != v.dimension())
        throw new std::runtime_error("MATRIX VECTOR DIM MISMATCH");

    vec u(v.dimension());

    for(nnum j=0; j<m.d_col(); j++) {
        u[j] = 0;
        for(nnum i=0; i<m.d_row(); i++){
            u[j] += m[i][j] * v[i];
        }
    }

    return u;
}


std::ostream& operator<<(std::ostream &os, const matrix& m)
{
    for(nnum i=0; i<m.d_row(); i++){
        os << "| ";
        for(nnum j=0; j<m.d_col(); j++) {
            os << m[i][j];
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
        m[i][i] = 1;
    }
    return m;
}

matrix matrix::repl_row(nnum r, vec v) const
{
    if(d_row() != v.dimension())
        throw new std::runtime_error("RREPL MATRIX VECTOR DIM MISMATCH");

    matrix m(*this);
    m[r] = v.get();

    return m;
}

matrix matrix::repl_col(nnum c, vec v) const
{
    if(d_col() != v.dimension())
        throw new std::runtime_error("CREPL MATRIX VECTOR DIM MISMATCH");

    matrix m(*this);
    for(nnum i = 0; i < this->d_col(); i++)
        m[i][c] = v[i];

    return m;
}


vec matrix::get_row(nnum r) const
{
    if(r >= d_row())
        throw new std::runtime_error("ROW TOO LARGE");

    vec temp(d_col());
    temp = (*this)[r];

    return temp;
}

vec matrix::get_col(nnum c) const
{
    if(c >= d_col())
        throw new std::runtime_error("COL TOO LARGE");

    vec temp(d_row());
    for(nnum i = 0; i < temp.dimension(); i++) {
        temp[i] = (*this)[i][c];
    }

    return temp;
}

vec matrix::to_vec() const
{
    if(d_col()==1){
        return get_col(0);
    } else if(d_row() == 1){
        return get_row(0);
    } else {
        throw new std::runtime_error("MATIX NOT IN VECTOR FORM");
        return vec(0);
    }
}

matrix matrix::del(nnum row, nnum col) const
{
    matrix m(dim_row-1, dim_col-1);

    for(nnum i=0; i<dim_row; i++) {
        for(nnum j=0; j<dim_col; j++) {
            nnum i_new = i;
            nnum j_new = j;

            if(i == row || j == col) continue;
            if(i > row) i_new--;
            if(j > col) j_new--;


            m[i_new][j_new] = (*this)[i][j];
        }
    }

    return m;
}

matrix matrix::transpose() const
{
    matrix m(dim_col, dim_row);
    for(nnum i=0; i<dim_row; i++) {
        for(nnum j=0; j<dim_col; j++) {
            m[j][i] = (*this)[i][j];
        }
    }
    return m;
}

rnum matrix::det() const
{
    if(dim_row != dim_col)
        throw new std::runtime_error("DET NOT SQUARE");

    if(dim_row == 1)
        return (*this)[0][0];

    rnum sum = 0;

    for(nnum i=0; i < dim_col; i++) {
        matrix m = this->del(0,i);
        if((*this)[0][i])
            sum += (i%2?-1:1) * (*this)[0][i] * m.det();
    }

    return sum;
}

matrix matrix::adj() const
{
    matrix m(dim_col, dim_row);
    matrix temp(*this);
    for(nnum i=0; i<dim_row; i++) {
        for(nnum j=0; j<dim_col; j++) {
            m[i][j] = std::pow(-1, i+j) * temp.del(i,j).det();
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

    return m * (1/det);
}

std::pair<matrix, matrix> matrix::QR_decomposition() const
{
    if(dim_col != dim_row)
        throw new std::runtime_error("QRDECOMP MATRIX NOT SQUARE");

    matrix U(dim_row, dim_col);
    matrix A_T(this->transpose());

    for(nnum i = 0; i<dim_row; i++){
        vec a(A_T[i]);
        vec u(a);

        for(nnum k = 0; k<i; k++){
            vec u_k = vec(U[k]);
            vec proj = (u_k * a) / (u_k * u_k) * u_k;
            u += -1 * proj;
        }

        for(nnum j = 0; j<dim_row; j++){
            U[i][j] = u[j];
        }
    }

    matrix Q(U);

    for(nnum i = 0; i<dim_row; i++){
        vec u(Q[i]);
        rnum len = u.len();

        for(nnum j = 0; j<dim_row; j++){
            Q[i][j] /= len;
        }
    }

    matrix R(dim_row, dim_col);

    for(nnum j = 0; j<dim_col; j++){
        for(nnum i = 0; i<=j; i++){
            R[i][j] = vec(Q[i]) * vec(A_T[j]);
        }
    }

    U = U.transpose();
    Q = Q.transpose();

    return std::pair<matrix,matrix>(Q,R);
}

#define EV_QR_ITERATIONS 20
vec matrix::eigenvalues() const
{
    if(dim_col != dim_row)
        throw new std::runtime_error("EV CALC MATRIX NOT SQUARE");

    matrix m(*this);
    for(nnum i = 0; i<EV_QR_ITERATIONS; i++) {
        std::pair<matrix,matrix> qr = m.QR_decomposition();
        m = qr.second * qr.first;
    }

    vec v(dim_col);
    for(nnum i = 0; i < v.dimension(); i++) {
        v[i] = m[i][i];
    }
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

std::vector<vec> matrix::eigenvectors() const
{
    std::vector<vec> v;
    vec ev = eigenvalues();
    for(nnum i = 0; i < ev.dimension(); i++) {
        v.push_back(ev[i]);
    }
    return v;
}

#define EV_INVIT_ITERATIONS 10
#define EV_INVIT_OFFSET 0.01
vec matrix::eigenvector_to(rnum eigenvalue) const
{
    if(dim_col != dim_row)
        throw new std::runtime_error("MAX EV CALC MATRIX NOT SQUARE");

    vec v(dim_row);
    v[0] = 1;
    if(dim_row > 1)
        v[1] = std::sqrt(M_PI);

    matrix m(((*this) - ((eigenvalue-EV_INVIT_OFFSET)*matrix::unit(dim_row))).inverse());

    for(nnum i = 0; i<EV_INVIT_ITERATIONS; i++) {
        vec temp = m*v;
        v = temp*(1/temp.len());
    }

    return v;
}

#define EV_POWER_ITERATIONS 20
vec matrix::max_eigenvector() const
{
    if(dim_col != dim_row)
        throw new std::runtime_error("MAX EV CALC MATRIX NOT SQUARE");

    vec v(dim_row);
    v[0] = 1;
    if(dim_row > 1)
        v[1] = std::sqrt(M_PI);

    for(nnum i = 0; i<EV_POWER_ITERATIONS; i++) {
        vec temp = (*this)*v;
        v = temp*(1/temp.len());
    }

    return v;
}


















