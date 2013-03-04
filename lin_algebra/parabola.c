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
  FILE *out;
  int i,j;
  int n_rows, n_columns;
  float *mtiempo; 


 in = fopen( argv[1] , "r");

n_rows = contarlineas(argv[1]);
n_columns = 2;

 
/* incialisa las matrices y los vectores*/

   gsl_matrix *matriz = gsl_matrix_calloc (n_rows, n_columns);    
   gsl_matrix *g = gsl_matrix_calloc (n_rows, 3);   
   gsl_matrix *gTg = gsl_matrix_calloc (3,3);
   gsl_matrix *inversa = gsl_matrix_calloc (3,3);  
   gsl_vector *t = gsl_vector_calloc (n_rows);
   gsl_vector *pos = gsl_vector_calloc (n_rows);     
   gsl_vector *gTd = gsl_vector_calloc (3);   
   gsl_vector *m = gsl_vector_calloc (3);
  


   // se crear la matriz con los datos del archivo
   gsl_matrix_fscanf (in, matriz);
  
   // se separa la matris en vectores
   gsl_matrix_get_col (t, matriz, 0);
   gsl_matrix_get_col (pos, matriz, 1);
  
   /* crea g*/
   crearg (t, g, n_rows);  
   /* se crea (G^T) * G */
   gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, g, g, 0.0, gTg);  
   /* se crea  [(G^T) * G]^(-1) */ 
   invertirmatriz (gTg, inversa, 3);  
   /* se crea  (G^T) * d */
   gsl_blas_dgemv (CblasTrans, 1.0, g, pos, 0.0, gTd);  
   /* se obtiene m */
   gsl_blas_dgemv (CblasNoTrans, 1.0, inversa, gTd, 0.0, m);
  

   /* imprime el archivo con los valores de m*/ 
  out = fopen("parametros_movimiento.dat", "w");
  fprintf(out, "%f %f %f" ,gsl_vector_get (m, 0), gsl_vector_get (m, 1) ,gsl_vector_get (m, 2)); 


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


/* crea la matriz [1 t 1/2 t*t] */

int crearg (gsl_vector* mtiempo, gsl_matrix* answer, int size)
{
  gsl_vector* cte = gsl_vector_calloc( size );
  gsl_vector* tt = gsl_vector_calloc( size );

  gsl_vector_set_all (cte , 1.0);
  gsl_vector_add (tt,mtiempo);
  gsl_vector_mul (tt, mtiempo);
  gsl_vector_scale (tt, 0.5);

  gsl_matrix_set_col (answer, 0, cte);
  gsl_matrix_set_col (answer, 1, mtiempo);
  gsl_matrix_set_col (answer, 2, tt);	
  
   return 0;
}

/*invierte la matriz*/

int invertirmatriz  (gsl_matrix * m, gsl_matrix * inversa, int n)
{

   int s;
  gsl_permutation * perm = gsl_permutation_alloc (n);

  gsl_linalg_LU_decomp (m, perm, &s);
  gsl_linalg_LU_invert (m, perm, inversa);
 
  return 0;
}



 
 
