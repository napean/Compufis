#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>

int contarlineas (char *filename);

int main (int argc, char** argv)
{
 
  FILE *in;
  in = fopen(argv[1], "r");

  int n_rows;
  int n_columns;

  n_columns = 3;
  n_rows  = contarlineas(argv[1]);

  gsl_matrix *matriz = gsl_matrix_calloc (n_rows, n_columns);
  gsl_matrix* comatriz = gsl_matrix_calloc ( n_columns,  n_columns);
  gsl_matrix* eigenvectors = gsl_matrix_calloc ( n_columns,  n_columns);
  gsl_vector* eigenvalues = gsl_vector_calloc ( n_columns );

  gsl_matrix_fscanf (in, matriz);
  matrizcovariansa (matriz,  n_columns, n_rows,  comatriz);
  get_eigen ( comatriz , eigenvalues, eigenvectors,  n_columns);
  creararch (eigenvectors);

}


double promedio (gsl_vector* vector, int n)
{
  int i;
  double prom;
  prom = 0;
  for(i = 0 ; i < n ;i++)
    {
      prom += gsl_vector_get(vector,i);
    }
  prom  /= (n);

  return prom;
}


double covariansa(gsl_matrix* matriz, int i, int j, int n, int m)
{
  gsl_vector* di = gsl_vector_calloc (m);
  gsl_vector* dj = gsl_vector_calloc (m);
  gsl_matrix_get_col (di, matriz, i);
  gsl_matrix_get_col (dj, matriz, j);

  int k;
  double covariance;
  covariance = 0;
  for (k = 0 ; k < m ; k++)
    {
      double dik = gsl_vector_get (di,k);
      double djk = gsl_vector_get (dj,k);


      covariance +=((dik-promedio(di,m))*(djk-promedio(dj,m)));
    }

  covariance /= (m-1);

  return covariance;

}

int matrizcovariansa(gsl_matrix* matriz, int n, int m, gsl_matrix* comatriz)
{
  int i;
  int j;

  for (i = 0; i < n; i ++)
    {
      for (j = 0; j < n; j ++)
	{

	  gsl_matrix_set(comatriz, i , j ,covariansa(matriz, i, j, n, m));
	}
    }
}

int contarlineas (char *filename){

  FILE *arch;
  int lineas;
  int test;

 arch = fopen(filename, "r");

 if(!arch)
{
     printf("problem opening file %s\n", filename);
     exit(1);
   }

lineas = 0;

 /* encuentra el numero de lineas*/
do{
  test =  fgetc(arch);
  if(test == '\n'){
    lineas++;}   
 }while(test!=EOF);

 return lineas;
}



int get_eigen (gsl_matrix* m,gsl_vector* eval, gsl_matrix* evec, int n)
{
  gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (n);
  
  gsl_eigen_symmv (m, eval, evec, w);
  
  gsl_eigen_symmv_free (w);
  
  gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_ASC);

return 0;
}

int crearcarh (gsl_matrix* input)
{
  FILE *out;
  out = fopen("autovectores_3D_data.dat", "w");
  gsl_matrix_swap_columns (input, 0, 2);

  fprintf(out , "%f %f %f \n %f %f %f \n %f %f %f" ,gsl_matrix_get (input, 0,0), gsl_matrix_get (input, 1,0) ,gsl_matrix_get (input, 2,0),gsl_matrix_get (input, 0,1), gsl_matrix_get (input, 1,1) ,gsl_matrix_get (input, 2,1),gsl_matrix_get (input, 0,2), gsl_matrix_get (input, 1,2) ,gsl_matrix_get (input, 2,2));

return 0;
}
