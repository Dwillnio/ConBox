#include "polynom.h"


polynom::polynom(rnum constant, nnum power) : coeff(power+1, 0)
{
    coeff[power] = constant;
}


nnum polynom::crop()
{
    nnum count = 0;
    for(nnum i = coeff.size()-1; i > 0; i--){
        if(!coeff[i])
            count++;
        else
            break;
    }

    for(; count > 0; count--){
        coeff.pop_back();
    }

    return coeff.size()-1;
}

polynom polynom::mult(nnum power) const
{
    polynom p(*this);

    for(nnum i = 0; i < power; i++){
        auto it = p.coeff.begin();
        p.coeff.insert(it,0);
    }

    return p;
}


rnum polynom::value(rnum x) const
{
    rnum sum = 0;
    for(nnum power = 0; power<coeff.size(); power++){
        sum += coeff[power] * std::pow(x,power);
    }
    return sum;
}

polynom polynom::zeros2polynom(std::vector<rnum> zeros)
{
    polynom p = 1;

    for(nnum i = 0; i < zeros.size(); i++) {
        polynom q(0,1);
        q[0] = -zeros[i];
        q[1] = 1;

        p *= q;
    }

    return p;
}

polynom& polynom::operator+=(const polynom& p)
{
    for(nnum i = coeff.size(); i < p.coeff.size(); i++){
        coeff.push_back(0);
    }

    for(nnum i = 0; i < p.coeff.size(); i++) {
        coeff[i] += p.coeff[i];
    }

    return *this;
}

polynom polynom::operator+(const polynom& p) const
{
    polynom q(*this);
    return q+=p;
}


polynom& polynom::operator-=(const polynom& p)
{
    for(nnum i = coeff.size(); i < p.coeff.size(); i++){
        coeff.push_back(0);
    }

    for(nnum i = 0; i < p.coeff.size(); i++) {
        coeff[i] -= p.coeff[i];
    }

    return *this;
}

polynom polynom::operator-(const polynom& p) const
{
    polynom q(*this);
    return q-=p;
}


polynom& polynom::operator*=(const polynom& p)
{
    *this = *this * p;
    return *this;
}

polynom polynom::operator*(const polynom& p) const
{
    std::vector<polynom> vec;
    for(nnum power = 0; power < coeff.size(); power++){
        polynom q = coeff[power] * p.mult(power);
        vec.push_back(q);
    }

    polynom sum(0);
    for(nnum i = 0; i < vec.size(); i++){
        sum += vec[i];
    }

    return sum;
}

int polynom::resize(nnum sz)
{
    int diff = coeff.size() - sz;
    if(diff > 0)
        for(nnum i = 0; i < diff; i++)
            coeff.pop_back();
    else if(diff < 0)
        for(nnum i = 0; i < -1*diff; i++)
            coeff.push_back(0);
    else
        return 0;

    return diff;
}

rnum& polynom::operator[](nnum c)
{
    if(c >= coeff.size())
        resize(c);

    return coeff[c];
}


rnum polynom::operator[](nnum c) const
{
    if(c >= coeff.size())
        return 0;

    return coeff[c];
}


polynom& polynom::operator*=(rnum r)
{
    for(nnum power = 0; power < coeff.size(); power++)
        coeff[power] *= r;

    return *this;
}

polynom polynom::operator*(rnum r) const
{
    polynom q(*this);
    return q*=r;
}

polynom operator*(rnum r, const polynom& p)
{
    return p*r;
}

std::ostream& operator<<(std::ostream &os, const polynom& p)
{
    polynom q(p);
    os << q[0];

    for(nnum i = 1; i <= q.deg(); i++){
        os << " + " << q[i] << "*x^" << i << std::flush;
    }

    return os;
}


vec func_dgl_polynom::value(rnum t, const vec& x, const vec& u, const vec& z) const
{
    if(x.dimension() != d_x() || u.dimension() != d_u())
        throw new std::runtime_error("POLYDGL DIMENSION MISMATCH");

    vec ret(d_x());

    for(nnum i = 0; i < ret.dimension()-1; i++)
        ret[i] = x[i+1];

    rnum sum = 0;
    for(nnum i = 0; i < q.deg_c()+1; i++){
        sum += q[i] * u[i];
    }
    for(nnum i = 0; i < p.deg_c(); i++){
        sum -= p[i] * x[i];
    }
    ret[ret.dimension()-1] = sum;

    return ret;
}















