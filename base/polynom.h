#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <cmath>
#include <iostream>

#include "base/definitions.h"
#include "base/func_dgl.h"

class polynom
{
public:
    polynom(const std::initializer_list<rnum>& coefficients) : coeff(coefficients) {if(coeff.empty()) coeff.push_back(0);}
    explicit polynom(rnum constant, nnum power);
    polynom(rnum constant) : polynom(constant,0) {}
    polynom() : polynom(0) {}

    rnum value(rnum x) const;

    nnum deg_c() const {return coeff.size()-1;}
    nnum deg() {crop(); return coeff.size()-1;}

    int resize(nnum sz);

    polynom& operator+=(const polynom& p);
    polynom operator+(const polynom& p) const;

    polynom& operator-=(const polynom& p);
    polynom operator-(const polynom& p) const;

    polynom& operator*=(const polynom& p);
    polynom operator*(const polynom& p) const;

    polynom& operator*=(rnum r);
    polynom operator*(rnum r) const;

    rnum& operator[](nnum c);
    rnum operator[](nnum c) const;

    polynom static zeros2polynom(std::vector<rnum> zeros);

protected:
    nnum crop();
    polynom mult(nnum power) const;

    std::vector<rnum> coeff;
};

class func_dgl_polynom : public func_dgl
{

public:
    // G(s) = q(s)/p(s) = Y(s)/U(s)
    func_dgl_polynom(const polynom& q_, const polynom& p_) : func_dgl(p_.deg_c(), q_.deg_c()+1, 0), q(q_), p(p_) {}

    //x_i = d^i/dt^i Y, u_i = d^i/dt^i U
    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z) const;

protected:
    polynom q,p;
};


polynom operator*(rnum r, const polynom& p);

std::ostream& operator<<(std::ostream &os, const polynom& p);


#endif // POLYNOM_H
