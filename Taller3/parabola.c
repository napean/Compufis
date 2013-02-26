#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

int contarlineas (char *filename);

int main(int argc, char **argv){

  FILE *in;
  int i,j;
  int n_rows, n_columns;
  float *mtiempo; 


 in = fopen( argv[1] , "r");

n_rows = contarlineas(argv[1]);
n_columns = 2;

 
/* incialisa las matrices y los vectores*/

   gsl_matrix *matriz = gsl_matrix_calloc (n_rows, n_columns);    
   gsl_matrix *g = gsl_matrix_calloc (n_rows, 3);   
   // gsl_matrix *g_trans = gsl_matrix_calloc (3,n_rows);    
   gsl_matrix *gTg = gsl_matrix_calloc (3,3);
   gsl_matrix *inve = gsl_matrix_calloc (3,3);  
   gsl_vector *t = gsl_vector_calloc (n_rows);
   gsl_vector *pos = gsl_vector_calloc (n_rows);     
   gsl_vector *gTd = gsl_vector_calloc (3);   
   gsl_vector *m = gsl_vector_calloc (3);
  


   // se crear la matriz con los datos del archivo
   gsl_matrix_fscanf (in, matriz);
  
   // se separa la matris en vectores
   gsl_matrix_get_col (t, matriz, 0);
   gsl_matrix_get_col (pos, matriz, 1);
  
   // G matrix is written
   write_g (t, g, n_rows);
  
   // (G^T) * G matrix is calculated
   gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, g, g, 0.0, gTg);
  
   // (G^T) * G is inverted and saved into [(G^T) * G]^(-1) matrix
   invert_matrix (gTg, inve, 3);
  
   // (G^T) * d vector is calculated
   gsl_blas_dgemv (CblasTrans, 1.0, g, pos, 0.0, gTd);
  
   // m vector is calculated
   gsl_blas_dgemv (CblasNoTrans, 1.0, inve, gTd, 0.0, m);
  
   // exports parameters into file
   print_file(m);


   return 0;
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


int write_g (gsl_vector* time, gsl_matrix* answer, int size)
{
  gsl_vector* one = gsl_vector_calloc( size );
  gsl_vector* time_squared = gsl_vector_calloc( size );

  gsl_vector_set_all (one, 1.0);
  gsl_vector_add (time_squared, time);
  gsl_vector_mul (time_squared, time);
  gsl_vector_scale (time_squared, 0.5);

  gsl_matrix_set_col (answer, 0, one);
  gsl_matrix_set_col (answer, 1, time);
  gsl_matrix_set_col (answer, 2, time_squared);	
  
   return 0;
}



int invert_matrix (gsl_matrix * m, gsl_matrix * inverse, int n)
{

   int s;

  gsl_permutation * perm = gsl_permutation_alloc (n);

  gsl_linalg_LU_decomp (m, perm, &s);
  gsl_linalg_LU_invert (m, perm, inverse);
 
return 0;
}

int print_file (gsl_vector* input)
{
  FILE *export;
  export = fopen("parametros_movimiento.dat", "w");

  fprintf(export, "%f %f %f" ,gsl_vector_get (input, 0), gsl_vector_get (input, 1) ,gsl_vector_get (input, 2));

return 0;
}

 
 
