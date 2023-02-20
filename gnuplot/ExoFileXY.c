#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float f(float x, float y);
float xn(int n, float h);
float g(float z, float h, int n, float yn0);   // variable z, const h, index n, yn0 = y[n-1]
float gprime(float h, int n);                // Dérivé de g(z)
float y(float yn0, float h, int n);         // yn0 = y[n-1]
void drawWithPlot(char* fileCoords);
void makeFile(int* n, float* y0, float* yn, float* x, float h);


int main(){
    printf("Exo Mr Robinson\n");
    printf("Exo %g\n",cos(2*0.9));
    printf("pomme de terre f(a) = %g && f(b) = %g \n", sin(2*0.2) - 1 + 0.2, sin(2));
/// Données
    float h = 0.05f;
    float y0 = 2.f;
    int n = 1;
    float x = 7.f;
    float yn = 77.f;

/// Traitement
    //makeFile(&n, &y0, &yn, &x, h);
    FILE *exograph = fopen("./exograph.txt", "w");
    if(exograph){
        fprintf(exograph, "%g %g\n",0.f,y0);       /* x[0] & y[0] */

        for (;n<=20; n++)                           /* 0 <= x[n] <= 2 pour x[n] = n/10 */
        {
            x = n/10.f;
            printf("x[n] = %g \t",x);
            yn = y(y0, h, n);
            printf("y[n] = %g\n",yn);

            y0 = yn;
            fprintf(exograph, "%g %g\n",x,yn);     /* x[n] & y[n] */
        }
        fclose(exograph);

    }else printf("exograph.txt not found");

    

/// Sortie
    //drawWithPlot("exograph.txt");
    printf("\n--END--\n");

    return 0;
}

float f(float x, float y){
    float val = pow(x,2) * exp(-x) - ((3 * pow(x,2)) + 1)*y;
    return val;
}

float g(float z, float h, int n, float yn0){
    float val = z - yn0 - (h*f(xn(n,h),z));
    return val;
}

float gprime(float h, int n){
    float x = xn(n,h);
    return (1 + (h * ( (3 * pow(x,2)) + 1)));
}

float y(float yn0, float h, int n){
    return (yn0 + ((h*f(xn(n,h),yn0))/gprime(h,n)) );
}

float xn(int n, float h){
    float val = n/10;
    return val;
}

void drawWithPlot(char* fileCoords){
    FILE *gnuplotPipe = popen("/opt/homebrew/bin/gnuplot -persist", "w");
    if (gnuplotPipe){
        fprintf(gnuplotPipe, "set terminal qt size 800,600 \n");
        fprintf(gnuplotPipe, "set title 'Resultat des mesures' \n");

        fprintf(gnuplotPipe, "set style data linespoints \n");
        //fprintf(gnuplotPipe, "set datafile separator \";;\" \n");

        fprintf(gnuplotPipe, "plot '%s' w lp lw 2, (exp(-x)/3)*(5*exp(-x*x*x)+1)\n",fileCoords);

        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    }else{
        printf("Gnuplot not found");
    }
}

void makeFile(int* n, float* y0, float* yn, float* x, float h){
    FILE *exograph = fopen("./exograph.txt", "w");
        fprintf(exograph, "%g %g\n",0.f,y0);       /* x[0] & y[0] */

        for (;*n<=20; *n++)                           /* 0 <= x[n] <= 2 pour x[n] = n/10 */
        {
            *x = *n/10.f;
            printf("x[n] = %g \t",*x);
            *yn = y(*y0, h, *n);
            printf("y[n] = %g\n",*yn);

            *y0 = *yn;
            fprintf(exograph, "%g %g\n",x,yn);     /* x[n] & y[n] */
        }
        fclose(exograph);
}