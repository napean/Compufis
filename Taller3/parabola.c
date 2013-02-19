#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

int main(int argc, char **argv){

float *I;
int i,j;
 int n_row, n_columns;
 float *data;

data = load_data(argv[1], &n_row , &n_columns);


 return 0;

}
 
float *load_data(char *in, int *n_row , int *n_columns){


  FILE *arch;
  float *matriz;
 int lineas = 0;
  
int i,j;

 arch = fopen(in,'r');

 /* encuentra el numero de lineas*/
do{
  test =  fgetc(arch);
  if(test == '\n'){
    lineas++;}
      i+=1;      
  }while(test!=EOF) 

 matriz  = malloc (lineas * 2 * sizeof(float));

 *n_row = lineas;
 *n_columns = 2;
 
 /* do{
    test =  fscanf(in, "%d %d\n", pos[i], tiempo[i]) 
      i+=1;
        }while(test!=EOF);*/


 /* inicialisa la matriz*/
 for(i=0;i< lineas;i++){
   /*for(j=0;j<n_columns;j++){
      pos = j + (n_columns * i); position in the array*/
      
      fscanf(arch, "%d %d\n", matriz[i], matriz[i+1]);
           
    }
  


 fclose(in);
 return matriz;

}
