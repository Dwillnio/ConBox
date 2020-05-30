#ifndef FUNC_DGL_H
#define FUNC_DGL_H

#include "function.h"

class func_dgl{

public:
    func_dgl(vec (*f) (rnum t, const vec& x, const vec& u, const vec& z), int d_x, int d_u, int d_z) :
        func(f), dim_x(d_x), dim_u(d_u), dim_z(d_z) {};

    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z) const;

    unsigned const int d_x() const {return dim_x;}
    unsigned const int d_u() const {return dim_u;}
    unsigned const int d_z() const {return dim_z;}

private:
    unsigned const int dim_x, dim_u, dim_z;
    vec (*func) (rnum t, const vec& x, const vec& u, const vec& z);
};

#endif // FUNC_DGL_H
