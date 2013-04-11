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
	int al;
	int times;

  h = 0.001;
  n_points =((30.0+h)/h);
  i=0;

  float *t;
  float *y_1;
  float *y_2;
  float *y_3;
	float *aleatorios;

  t = malloc(n_points * sizeof(float));
  y_1 = malloc(n_points * sizeof(float));
  y_2 = malloc(n_points * sizeof(float));
  y_3 = malloc(n_points * sizeof(float));
	aleatorios = malloc(30 * sizeof(float));


	for ( al = 0; al < 30 ; al ++){
	
		if (al/2){
		aleatorios[al] = rand()%10;
		} else{
		aleatorios[al]	= -1*rand()%10; 
		}
	
	}

	

	for ( times = 0; times < 30 ; times +=3)
	{
		t[0] = 0;
		y_1[0] = aleatorios[times];
		y_2[0] = aleatorios[times+2];
		y_3[0] = aleatorios[times+1];

		for (i=1; i< n_points ; i++){

			float y_prime1 = funprim1(t[i-1], y_1[i-1], y_2[i-1], y_3[i-1]);
			float y_prime2 = funprim2(t[i-1], y_1[i-1], y_2[i-1], y_3[i-1]);
			float y_prime3 = funprim3(t[i-1], y_1[i-1], y_2[i-1], y_3[i-1]);
			
		/* primer paso */		
			float tmedio1 = t[i-1] + (h/2.0);
			float y1medio1 = y_1[i-1] + (h/2.0)*y_prime1;
			float y2medio1= y_2[i-1] + (h/2.0)*y_prime2;
			float y3medio1 = y_3[i-1] + (h/2.0)*y_prime3;
				
			float  ymedioprima1_1 = funprim1(tmedio1, y1medio1, y2medio1, y3medio1);
			float  ymedioprima2_1 = funprim2(tmedio1, y1medio1, y2medio1, y3medio1);
			float  ymedioprima3_1 = funprim3(tmedio1, y1medio1, y2medio1, y3medio1);
			
		/* segundo paso */	
			float tmedio2 = t[i-1] + (h/2.0);
			float y1medio2 = y_1[i-1] + (h/2.0)*ymedioprima1_1;
			float y2medio2= y_2[i-1] + (h/2.0)*ymedioprima2_1;
			float y3medio2 = y_3[i-1] + (h/2.0)*ymedioprima3_1;
				
			float  ymedioprima1_2 = funprim1(tmedio2, y1medio2, y2medio2, y3medio2);
			float  ymedioprima2_2 = funprim2(tmedio2, y1medio2, y2medio2, y3medio2);
			float  ymedioprima3_2 = funprim3(tmedio2, y1medio2, y2medio2, y3medio2);

	/* tercer paso */	
			float tmedio3 = t[i-1] + (h/2.0);
			float y1medio3 = y_1[i-1] + (h/2.0)*ymedioprima1_2;
			float y2medio3= y_2[i-1] + (h/2.0)*ymedioprima2_2;
			float y3medio3 = y_3[i-1] + (h/2.0)*ymedioprima3_2;
				
			float  ymedioprima1_3 = funprim1(tmedio3, y1medio3, y2medio3, y3medio3);
			float  ymedioprima2_3 = funprim2(tmedio3, y1medio3, y2medio3, y3medio3);
			float  ymedioprima3_3 = funprim3(tmedio3, y1medio3, y2medio3, y3medio3);

	/* tercer paso */

			float ymedioprima1 = (y_prime1 + 2.0* ymedioprima1_1 + 2.0*ymedioprima1_2 + ymedioprima1_3)/6.0;
			float ymedioprima2 = (y_prime1 + 2.0* ymedioprima2_1 + 2.0*ymedioprima2_2 + ymedioprima2_3)/6.0;
			float ymedioprima3 = (y_prime3 + 2.0* ymedioprima3_1 + 2.0*ymedioprima3_2 + ymedioprima3_3)/6.0;

				
			t[i] = t[i-1] + h;
			y_1[i] = y_1[i-1] + h * ymedioprima1 ;
			y_2[i] = y_2[i-1] + h * ymedioprima2 ;
			y_3[i] = y_3[i-1] + h * ymedioprima3 ;
		  
  	}

		char nom[15];
		sprintf(nom, "valores%d.dat", times);

		FILE *out;
		out = fopen( nom , "w");
	
		if (! out){
	
			printf( "hubo un problema al abrir el archivo");
			exit(1);
		}	

		for ( w = 0; w < n_points ; w++){

			fprintf(out, "%f %f %f %f\n" ,t[w], y_1[w], y_2[w], y_3[w]);

		}

		fclose (out);
				
	}
}
