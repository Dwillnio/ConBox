#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Dense>

#include "definitions.h"
#include "vec.h"
#include "cnum.h"

using Eigen::MatrixXd;
using Eigen::VectorXcd;

class matrix : public MatrixXd
{
public:
    matrix(const MatrixXd& m) : MatrixXd(m) {}

    matrix(const std::vector<std::vector<rnum>>& entries)  : MatrixXd(entries.size(), entries[0].size())
    {
        for(nnum i = 0; i < entries.size(); i++){
            for(nnum j = 0; j < entries[0].size(); j++){
                (*this)(i,j) = entries[i][j];
            }
        }
    }

    matrix(const std::vector<rnum>& entries, nnum dim_r)  : MatrixXd(dim_r, entries.size()/dim_r)
    {
        nnum sz = entries.size();
        if(sz % dim_r)
            throw new std::runtime_error("INVALID MATRIX CONSTRUCTOR INPUT");

        for(nnum i=0; i<rows(); i++){
            for(nnum j=0; j<cols(); j++) {
                (*this)(i,j) = entries[i*cols() + j];
            }
        }
    }

    matrix(const vec& v)  : MatrixXd(v.dimension(), 1)
    {
        *this = (*this).repl_col(0,v);
    }

    matrix(nnum dim_r, nnum dim_c) : MatrixXd(MatrixXd::Zero(dim_r, dim_c)) {}


    matrix operator* (rnum d) const;
    matrix& operator*= (rnum d);


    matrix operator* (const matrix& m) const;
    matrix& operator*= (const matrix& m);

    vec operator* (const vec& v) const;

    matrix operator+ (const matrix& m) const;
    matrix& operator+= (const matrix& m);
    matrix operator- (const matrix& m) const;
    matrix& operator-= (const matrix& m);

    matrix& operator=(const MatrixXd& m) {MatrixXd::operator=(m); return *this;}

    matrix repl_row(nnum r, vec v) const;
    matrix repl_col(nnum c, vec v) const;
    vec col(nnum c) const;
    vec row(nnum r) const;

    matrix del(nnum row, nnum col) const;
    matrix transpose() const;
    rnum det() const;
    matrix adj() const;
    matrix inverse() const;

    std::pair<matrix, matrix> QR_decomposition() const;

    VectorXcd eigenvalues() const;
    rnum max_eigenvalue() const;
    std::vector<Eigen::VectorXcd> eigenvectors() const;
    vec eigenvector_to(rnum eigenvalue) const;
    vec max_eigenvector() const;

    MatrixXd eigenrep() const {return MatrixXd(*(reinterpret_cast<const MatrixXd*>(this)));}

    static matrix unit(nnum d);
};


matrix operator* (rnum d, const matrix& m);
vec operator* (const vec& v, const matrix& m);

std::ostream& operator<<(std::ostream &os, const matrix& m);

#endif // MATRIX_H
