#ifndef CNUM_H
#define CNUM_H

#include <vector>

#include "definitions.h"
#include "vec.h"

class cnum
{
public:
    cnum() : real(0), imag(0) {}
    cnum(rnum r) : real(r), imag(0) {}
    cnum(rnum r, rnum i) : real(r), imag(i) {}
    cnum(std::vector<rnum> v)
    {
        if(v.size() < 2)
            throw new std::runtime_error("ERROR INIT COMPLEX NUMBER");

        real = v[0];
        imag = v[1];
    }

    cnum operator+ (cnum c) const;
    cnum& operator+= (cnum c);

    cnum operator- (cnum c) const;
    cnum& operator-= (cnum c);

    cnum operator* (cnum c) const;
    cnum& operator*= (cnum c);

    cnum operator/ (cnum c) const;
    cnum& operator/= (cnum c);

    /*
    cnum operator+ (rnum r) const;
    cnum& operator+= (rnum r);

    cnum operator- (rnum r) const;
    cnum& operator-= (rnum r);

    cnum operator* (rnum r) const;
    cnum& operator*= (rnum r);

    cnum operator/ (rnum r) const;
    cnum& operator/= (rnum r);
    */
    rnum real, imag;
};

std::ostream& operator<<(std::ostream &os, const cnum& c);

#endif // CNUM_H
