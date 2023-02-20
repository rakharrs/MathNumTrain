#include <stdio.h>
#include <stdlib.h>

float pj(int j, float x, float* xd, int dim);

float lagrange(float x, float *xd, float *yd, int dim);

void getdata(float** xd, float** yd);

float** alloc2D(int l, int c);

void gpDraw();

void buildLagrangeDB(char* datablockName,FILE* gp, float* xd, float*yd);
void buildCurveDB(char* datablockName, FILE* gp, float* xd, float* yd, int length);

int main(){

    printf(" - Interpolation -\n ");

/// Initialisation des données
    float* xd = NULL;
    float* yd = NULL;
    int dim = 7;
    float x = 0;
    getdata(&xd, &yd);

/// Traitement
    FILE* GP = popen("/opt/homebrew/bin/gnuplot -persist", "w");
    
    buildCurveDB("data1", GP, xd, yd, dim);
    buildLagrangeDB("data2", GP, xd, yd);

/// Sortie

    fprintf(GP, "plot $data1 using 1:2 w linespoints lc 'purple', %s, %s",
    "$data2 using 1:2 w linespoints lc 'red' pointtype 7 lw 3 t 'linear'",
    "$data1 using 1:2 w linespoints lc 'black' smooth csplines\n");

    fflush(GP);
    fclose(GP);
    
    return 0;
}

void buildLagrangeDB(char* datablockName, FILE* gp, float* xd, float*yd){
    fprintf(gp, "$%s << EOF \n",datablockName);
    for (float i = 0.f; i < 6; i+=0.01){        
        fprintf(gp, "%f %f\n", i, lagrange(i, xd, yd, 7));
    }
    fprintf(gp, "EOF\n");
}

void buildCurveDB(char* datablockName, FILE* gp, float* xd, float* yd, int length){
    fprintf(gp, "$%s << EOF \n",datablockName);
    for (int i = 0; i < length; i++){        
        fprintf(gp, "%f %f\n", xd[i], yd[i]);
    }
    fprintf(gp, "EOF\n");
}


void getdata(float** xd, float** yd){
    float* x = malloc(sizeof(float) * 7);
    float* y = malloc(sizeof(float) * 7);

    x[0] = 0;       y[0] = 0;
    x[1] = 0.5;     y[1] = 0.75;
    x[2] = 2;       y[2] = 0;
    x[3] = 3.2;     y[3] = 1.5;
    x[4] = 4;       y[4] = -0.75;
    x[5] = 4.8;     y[5] = -1;
    x[6] = 6;       y[6] = 0.5;
    *xd = x; *yd = y;
}

float pj(int j, float x, float* xd, int dim){
    float pjv = 1.0;
    for (int k = 0; k < dim; k++){
        if(k != j) {
            pjv *= ((x - xd[k]) / (xd[j] - xd[k]));
        }
    }
    return pjv;
}

float lagrange(float x, float *xd, float *yd, int dim){
    int j = 0;
    float y = 0;
    for (int j = 0; j < dim; j++){
        y += (yd[j] * pj(j,x,xd,dim));
    }
    return y;
}

float** alloc2D(int l, int c){
	float**a = malloc(l*sizeof(float*));
	for(int i=0; i<l;i++){
		a[i] = malloc(c*sizeof(float));
	}
	return a;
}