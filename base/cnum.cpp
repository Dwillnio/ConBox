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
    rnum temp = real * c.real - imag * c.imag;
    imag = real * c.imag + imag * c.real;
    real = temp;

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

    return *this;
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
