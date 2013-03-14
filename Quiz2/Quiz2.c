#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

float  myfuncion ( double x);

int main (int argc, char** argv){

  float a = atof(argv[1]);
  float b = atof(argv[2]);
  float paso = atof(argv[3]);
  float i;

  float h = (b-a)*paso;
  float integral = 0;

  /* int lista[(b-a)*h];



  for(i=a; i<b; i+=paso){
    
    lista[i] = myfuncion(i);

    }*/

  for(i=a; i<b; i+=h){
    
    integral += myfuncion(i)*h;

  }
  
    printf("%f\n", integral);

}

float  myfuncion ( double x){

  return ((1)/(sqrt(1+ cos(x)*sin(x))));
}


