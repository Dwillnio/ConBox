#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <vector>
#include <cmath>

#include "definitions.h"

class vec{
public:
    vec(const std::vector<rnum>& v) : dim(v.size()), values(v) {}
    vec(nnum i) : dim(i), values(std::vector<rnum>(i)) {}

    nnum dimension() const {return dim;}
    rnum len() const;
    const std::vector<rnum>& get() {return values;}

    rnum& operator[] (std::size_t n) {return values[n];}
    rnum operator[] (std::size_t n) const {return values[n];}
    vec operator* (rnum d) const;
    vec& operator*= (rnum d);
    vec operator+ (const vec& v) const;
    vec& operator+= (const vec& v);
    vec operator- (const vec& v) const;
    vec& operator-= (const vec& v);
    rnum operator* (const vec& v) const;

private:
    nnum dim;
    std::vector<rnum> values;
};

vec operator* (rnum d, const vec& v);
std::ostream& operator<<(std::ostream &os, const vec& v);

#endif // VEC_H
