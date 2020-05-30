#include "cnum.h"

cnum cnum::operator+ (cnum c) const
{
    cnum t = *this;
    t += c;

    return t;
}

cnum& cnum::operator+= (cnum c)
{
    this->real += c.real;
    this->imag += c.imag;

    return *this;
}

cnum cnum::operator- (cnum c) const
{
    cnum t = *this;
    t -= c;

    return t;
}

cnum& cnum::operator-= (cnum c)
{
    this->real -= c.real;
    this->imag -= c.imag;

    return *this;
}


cnum cnum::operator* (cnum c) const
{
    cnum t = *this;
    t *= c;

    return t;
}

cnum& cnum::operator*= (cnum c)
{
    this->real = real * c.real - imag * c.imag;
    this->imag = real * c.imag + imag * c.real;

    return *this;
}


cnum cnum::operator/ (cnum c) const
{
    cnum t = *this;
    t /= c;

    return t;
}

cnum& cnum::operator/= (cnum c)
{
    rnum len = c.real*c.real + c.imag * c.imag;
    cnum cinv(c.real/len, -c.imag/len);

    *this *= cinv;
}

/*
cnum cnum::operator+ (rnum r) const
{
    cnum t(r);
    return (*this)+t;
}

cnum& cnum::operator+= (rnum r)
{
    cnum t(r);
    *this += t;
    return (*this)+t;
}


cnum cnum::operator- (rnum r) const
{

}

cnum& cnum::operator-= (rnum r)
{

}


cnum cnum::operator* (rnum r) const
{

}

cnum& cnum::operator*= (rnum r)
{

}


cnum cnum::operator/ (rnum r) const
{

}

cnum& cnum::operator/= (rnum r)
{

}
*/

std::ostream& operator<<(std::ostream &os, const cnum& c)
{
    os << c.real << " + " << c.imag << "i";
    return os;
}
