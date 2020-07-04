#ifndef FUNC_D_DGL_H
#define FUNC_D_DGL_H

#include "function_d.h"
#include "func_dgl.h"

class func_d_dgl : public function_d, public func_dgl
{
public:
    func_d_dgl(nnum d_x, nnum d_u, nnum d_z, rnum dt_ = 1)
        : function_d(d_x+d_u+d_z, d_x), func_dgl(d_x, d_u, d_z) {}

    virtual vec value(nnum k, const vec& x, const vec& u, const vec& z) = 0;
    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z);
    virtual vec value(nnum k, const vec& x);

    vec operator() (nnum k, const vec& x, const vec& u, const vec& z)
    {return value(k, x, u, z);}

private:
    rnum dt;
};

#endif // FUNC_D_DGL_H
