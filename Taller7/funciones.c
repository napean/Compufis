#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

double G = (6.7E-8)*(1E34);

double funprim1  (double t, double r, double v){

  return v;
}

double funprim2  (double t, double r, double v)
{
  return (-(G)/(r*r)) + ((4*3.14*5.6E5*pow(1.7E12,5))/(1E29*r*r*r));
}

double funp  ( double r)
{
  return ((5.6E5)*pow((1.7E12),5))/(pow(r,5));
}

