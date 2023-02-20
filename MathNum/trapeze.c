#include <stdio.h> 
#include <math.h>

double f(double x);
int limitedarret(double eps, double a, double b);
double hah(double a, double b, int n);
double trapeze(double a, double b, int n);
double absolute(double n);

int main(){
///Initialisation
    double a, b, eps;
    int n;

///Entrée des données
    a = 0; b=1; eps = 1e-15;
    n=limitedarret(eps, a, b);

///Traitement
double val = trapeze(a,b,n);
    printf("exp(sin(5x) = %g",val);

}
double f(double x){
    return exp(sin(5*x));
}

double hah(double a, double b, int n){
    return (a-b)/n;
}

int limitedarret(double eps, double a, double b){
    double In, In1;
    int n=2;
    double h;
    while(absolute(In1-In) <= eps){
        /* calcul de In */
        h=hah(a,b,n);
        In = h/2*(f(a + (n + 1) * (hah(a,b,n))) - f(a + n * hah(a,b,n)));
        In1 = h/2*(f(a + (n + 1 + 1) * (hah(a,b,n + 1))) - f(a + n * hah(a,b,n + 1))); 
        n+=1;
    }
    return n;
}

double trapeze(double a, double b, int n){
    double somme=0;
    double h = hah(a,b, n);
    double val;
    for (int i = 0; i < n; i++)
    {
        h = hah(a,b,n);
        somme += f(a + i * h);
    }
    val = (h/2) * (f(a) + 2 * somme + f(b));
    return val;

}

double absolute(double n){
    return (n < 0) ? -1*n : n;
}

