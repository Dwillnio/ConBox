#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cmath>

#include "definitions.h"
#include "vec.h"

class matrix
{
public:
    matrix(const std::vector<std::vector<rnum>>& entries)  : dim_row(entries.size()), values(entries)
    {
        if(entries.size())
            dim_col=entries[0].size();
        else
            dim_col = 0;
    }

    matrix(const std::vector<rnum>& entries, nnum dim_r)  : dim_row(dim_r)
    {
        nnum sz = entries.size();
        if(sz % dim_row)
            throw new std::runtime_error("INVALID MATRIX CONSTRUCTOR INPUT");

        dim_col = sz / dim_row;

        for(nnum i=0; i<dim_row; i++){
            values.push_back(std::vector<rnum> ());
            for(nnum j=0; j<dim_col; j++) {
                values[i].push_back(entries[dim_row*i + j]);
            }
        }
    }

    matrix(nnum dim_r, nnum dim_c) : dim_row(dim_r), dim_col(dim_c)
    {
        for(nnum i=0; i<dim_row; i++){
            values.push_back(std::vector<rnum> ());
            for(nnum j=0; j<dim_col; j++) {
                values[i].push_back(0);
            }
        }
    }

    std::vector<rnum>& operator[] (std::size_t n) {return values[n];}
    std::vector<rnum> operator[] (std::size_t n) const {return values[n];}

    matrix operator* (rnum d) const;
    matrix& operator*= (rnum d);

    matrix operator* (const matrix& m) const;
    matrix& operator*= (const matrix& m);

    vec operator* (const vec& v) const;

    matrix operator+ (const matrix& m) const;
    matrix& operator+= (const matrix& m);
    matrix operator- (const matrix& m) const;
    matrix& operator-= (const matrix& m);

    nnum d_row() const {return dim_row;}
    nnum d_col() const {return dim_col;}

    matrix repl_row(nnum r, vec v) const;
    matrix repl_col(nnum c, vec v) const;
    vec get_row(nnum r) const;
    vec get_col(nnum c) const;

    vec to_vec() const;

    matrix del(nnum row, nnum col) const;
    matrix transpose() const;
    rnum det() const;
    matrix adj() const;
    matrix inverse() const;

    std::pair<matrix, matrix> QR_decomposition() const;
    vec eigenvalues() const;    //only real eigenvalues
    rnum max_eigenvalue() const;    //only real eigenvalues
    std::vector<vec> eigenvectors() const; //only real eigenvalues
    vec eigenvector_to(rnum eigenvalue) const; //only real eigenvalues
    vec max_eigenvector() const; //only real eigenvalues

    static matrix unit(nnum d);

private:
    nnum dim_row, dim_col;
    std::vector<std::vector<rnum>> values;
};

matrix operator* (rnum d, const matrix& m);
vec operator* (const vec& v, const matrix& m);
std::ostream& operator<<(std::ostream &os, const matrix& m);

#endif // MATRIX_H
