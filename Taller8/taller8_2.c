#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){
//uInitial Construction
    int nPoints = 100;
    float* x=malloc(nPoints * sizeof(float));
    float interval = 10.0/nPoints;
    x[0]=-5.0;
    int i=0;
	int cos = 0;
    for(i=1; i< nPoints;i++){
        x[i]=x[i-1]+ interval;
    }
    float* uInitial=malloc(nPoints * sizeof(float));
    for(i=0;i<nPoints;i++){
        uInitial[i]=exp(-x[i]*x[i]);
    }
//Firs Iteration
	float deltaX = x[1]-x[0];
	float deltaT = 0.00001;
	float alfa = deltaT/pow(deltaX,2);

	printf("%f", alfa);
//Fixed Boundary Conditions
	uInitial[0] = 0.0;
	uInitial[nPoints-1] = 0.0;
//Copy of the initial array
	float* uNew = malloc(nPoints * sizeof(float));
	for(i=0; i<nPoints; i++){
		uNew[i]=uInitial[i];
	}

//Doing it n times
	float nTimes = 3.0/deltaT;
	int j=0;
	for(j; j < nTimes; j++){
		for(i=1; i<nPoints-1;i++){
			uNew[i] = alfa*uInitial[i+1] + (1-(2*alfa))*uInitial[i] + alfa*uInitial[i-1];
		}

	if(j%30000==0){

	char nom[15];
	sprintf(nom,"segun%d.dat", j);
	FILE *out;
	out = fopen(nom,"w");
	int m=0;
		for(m;m<nPoints;m++){
			fprintf(out, "%f %f \n", x[m], uNew[m]);	
		}
	fclose(out);
		

	}
	for(cos =0; cos<nPoints; cos++){
			uInitial[cos]=uNew[cos];
		}
	
	}
	

}
