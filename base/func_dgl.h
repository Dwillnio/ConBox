#ifndef FUNC_DGL_H
#define FUNC_DGL_H

#include "function.h"

class func_dgl
{
public:
    func_dgl(int d_x, int d_u, int d_z) :
        dim_x(d_x), dim_u(d_u), dim_z(d_z) {};

    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z) = 0;

    unsigned int d_x() const {return dim_x;}
    unsigned int d_u() const {return dim_u;}
    unsigned int d_z() const {return dim_z;}

private:
    unsigned const int dim_x, dim_u, dim_z;
};

class func_dgl_p : public func_dgl
{
public:
    func_dgl_p(vec (*f) (rnum t, const vec& x, const vec& u, const vec& z), int d_x, int d_u, int d_z) :
        func_dgl(d_x, d_u, d_z), func(f){};

    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z);

private:
    vec (*func) (rnum t, const vec& x, const vec& u, const vec& z);
};

#endif // FUNC_DGL_H
