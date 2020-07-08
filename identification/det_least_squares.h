#ifndef DET_LEAST_SQUARES
#define DET_LEAST_SQUARES

#include "base/vec.h"
#include "base/matrix.h"

//deterministic recursive least squares estimator
class det_rlse
{

};

//  projects vector v onto subspace defined by img m
//  return projection
vec project_vector_subspace(const matrix& m, const vec& v);

//  projects vector v onto subspace defined by img m
//  returns necessary vector x, m*x = projection
vec project_vector_solution(const matrix& m, const vec& v);

#endif
