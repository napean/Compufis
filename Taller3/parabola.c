#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

void  *load_data(char *in, int *n_row , int *n_columns, float *mtiempo, float *pos);

int main(int argc, char **argv){


int i,j;
int n_row, n_columns;

 float *mtiempo;
 float *pos;


 load_data(argv[1], &n_row , &n_columns, mtiempo, pos);
 
 for( i = 0; i < n_row*3; i++) {
 
    printf("%f ", mtiempo[i]);
 }

 return 0;

}
 
void *load_data(char *in, int *n_row , int *n_columns, float *mtiempo, float *pos){

 FILE *arch;
 int test;
 float *tiempo;
 int lineas = 0;
 int i,j;
 int posi;

 arch = fopen(in,"r");

 /* encuentra el numero de lineas*/
do{
  test =  fgetc(arch);
  if(test == '\n'){
    lineas++;}   
 }while(test!=EOF);

 rewind(arch);

 pos  = malloc (lineas * sizeof(float));
 tiempo = malloc (lineas * sizeof(float));
 mtiempo = malloc (lineas *3* sizeof(float));

 *n_row = lineas;
 *n_columns = 2;


 /* inicialisa la matriz*/
 for(i=0;i< lineas;i++){
      
   fscanf(arch, "%f %f\n",(float)pos[i],(float)tiempo[i]);
           
    }

 /*crea la matriz de los tiempos*/
 for(i=0;i< lineas;i++){
   for(j=0;j<3;j++){
     posi = j + (3 * i);
	if(j==0){
	  mtiempo[posi]=1;}
        if(j==1){
	  mtiempo[posi]=tiempo[i];}
	if(j==2){
	  mtiempo[posi]=(1/2)*(tiempo[i])*(tiempo[i]);}
   }  
 }

 fclose(arch);

}
