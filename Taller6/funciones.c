#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>




float funprim1  (float t, float y_1, float y_2, float y_3){

  return 10.0*(y_2-y_1);
}

float funprim2  (float t, float y_1, float y_2, float y_3)
{
  return y_1*(28.0 - y_3) - y_2;
}

float funprim3  (float t, float y_1, float y_2, float y_3)
{
  return y_1*y_2 - (8.0/3.0)*y_3;
}


