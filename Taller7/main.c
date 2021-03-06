#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>
#include "funciones.h"


int main (void) { 

  float h;
  float n_points;
  int i;
  int w;

  h = 1000.0;
  n_points =((1500000.0+h)/h);
  i=0;

  double *t;
  double *r;
  double *v;
  double *p;

	double R =  1.7E12 / 1E12 ;
	double M = 1E34 / 1E34 ;
	double P = (5.6E5)/(1E12)*1E-5 ; 



  t = malloc(n_points * sizeof(double));
  r = malloc(n_points * sizeof(double));
  v = malloc(n_points * sizeof(double));
  p = malloc(n_points * sizeof(double));


	
	t[0] = 0;
	r[0] =  1.7E12;
	v[0] = 0;
	p[0] = (5.6E5);
 
		for (i=1; i< n_points ; i++){

			double rprime1 = funprim1(t[i-1], r[i-1], v[i-1]);
			double vprime1 = funprim2(t[i-1], r[i-1], v[i-1]);
			
			
		/* primer paso */		
			double tmedio1 = t[i-1] + (h/2.0);
			double rmedio1 = r[i-1] + (h/2.0)*rprime1;
			double vmedio1 = v[i-1] + (h/2.0)*vprime1;
			
				
			double rprime2 = funprim1(tmedio1, rmedio1, vmedio1);
			double vprime2 = funprim2(tmedio1, rmedio1, vmedio1);
			
			
		/* segundo paso */	
			double tmedio2 = t[i-1] + (h/2.0);
			double rmedio2 = r[i-1] + (h/2.0)*rprime2;
			double vmedio2 = v[i-1] + (h/2.0)*vprime2;
			
				
			double  rprime3 = funprim1(tmedio2, rmedio2, vmedio2);
			double  vprime3 = funprim2(tmedio2, rmedio2, vmedio2);
			

	/* tercer paso */	
			double tmedio3 = t[i-1] + (h/2.0);
			double rmedio3 = r[i-1] + (h/2.0)*rprime3;
			double vmedio3 = v[i-1] + (h/2.0)*vprime3;
			
				
			double  rprime4 = funprim1(tmedio3, rmedio3, vmedio3);
			double  vprime4 = funprim2(tmedio3, rmedio3, vmedio3);
			

	/* tercer paso */

			double rmedioprima1 = (1.0/6.0)*(rprime1 + 2.0* rprime2 + 2.0*rprime3 + rprime4);
			double vmedioprima2 = (1.0/6.0)*(vprime1 + 2.0* vprime2 + 2.0*vprime3 + vprime4);
			

				
			t[i] = t[i-1] + h;
			r[i] = r[i-1] + h * rmedioprima1 ;
			v[i] = v[i-1] + h * vmedioprima2 ;
			p[i] = funp(r[i]);
		  
  	}

		char nom[15];
		sprintf(nom, "valores%d.dat", 1);

		FILE *out;
		out = fopen( nom , "w");
	
		if (! out){
	
			printf( "hubo un problema al abrir el archivo");
			exit(1);
		}	

		for ( w = 0; w < n_points ; w++){

			fprintf(out, "%f %f %f %f\n" ,t[w], r[w], v[w], p[w]);

		}

		fclose (out); 
				
	
}
