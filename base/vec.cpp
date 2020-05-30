#include "vec.h"

rnum vec::len() const
{
    rnum sum = 0;
    for(nnum i = 0; i < dim; i++)
        sum += (*this)[i] * (*this)[i];

    return std::sqrt(sum);
}

vec& vec::operator*= (rnum d)
{
    for(unsigned int i = 0; i < dim; ++i)
        values[i] *= d;

    return *this;
}

vec vec::operator* (rnum d) const
{
    vec v(*this);
    v *= d;

    return v;
}

vec& vec::operator+= (const vec& v)
{
    if(v.dimension() != dimension())
        std::cerr << "Vector size mismatch\n";

    for(unsigned int i = 0; i < dim; ++i)
        values[i] += v[i];

    return *this;
}

vec vec::operator+ (const vec& v) const
{
    vec temp(*this);
    temp += v;

    return temp;
}

vec& vec::operator-= (const vec& v)
{
    if(v.dimension() != dimension())
        std::cerr << "Vector size mismatch\n";

    for(unsigned int i = 0; i < dim; ++i)
        values[i] -= v[i];

    return *this;
}

vec vec::operator- (const vec& v) const
{
    vec temp(*this);
    temp -= v;

    return temp;
}


rnum vec::operator* (const vec& v) const
{
    if(this->dimension() != v.dimension())
        throw new std::runtime_error("SCALAR PRODUCT DIM MISMATCH");

    rnum sum = 0;

    for(nnum i=0; i<this->dimension(); i++){
        sum += (*this)[i] * v[i];
    }

    return sum;
}

vec operator* (rnum d, const vec& v)
{
    return v * d;
}

std::ostream &operator<<(std::ostream &os, const vec& v)
{
    os << "[ ";
    for(nnum j=0; j<v.dimension(); j++) {
        os << v[j];
        os << " ";
    }
    os << "]";
    os << "\r\n";

    return os;
}
