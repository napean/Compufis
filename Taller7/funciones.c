#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

double R =  1.7E12 / 1E12 ;
double M = 1E31 / 1E31;
double t = 1 ;


double funprim1  (double t, double r, double v, double p){

  return v;
}

double funprim2  (double t, double r, double v, double p)
{
  return ((-(6.7E-11)*1E31/(r*r))+ (4*3.14*r*r*p)/1E29);
}

double funp  ( double r)
{
  return ((6.6E5)/1E24)*((1.7E17)/r);
}

