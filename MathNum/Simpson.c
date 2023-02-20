#include "stdio.h"
#include "math.h"

void displayResult(float a, float b, int n, float aire);
float f(float x);                                       /* La fonction */
float simpson(float a, float b, int n);                 /* Méthode d'intégration par la méthode de Simpson */
float integrate(float a, float b, float eps);

int main(){

    printf("Intégration par la méthode de Simpson \n\n");

/// Initialisation des données
    float a, b, aire;
    float eps;
    int n;

/// Entrée de donnée
    a = 0; b = 1; n = 7; eps = 1e-6;

/// Traitement
    aire = integrate(a, b, eps);

/// Solution
    displayResult(a, b, n, aire);

    return 0;
}

float integrate(float a, float b, float eps){
    int n =3;
    float aire1 = 0, aire2 = 1;
    aire1 = simpson(a, b, n);
    n+=2;
    aire2 = simpson(a, b, n);
    while(fabs(aire1 - aire2) > eps){
        aire1 = aire2;
        n+=2;
        aire2 = simpson(a,b,n);
    }
    printf("La valeur de n recuperee est : %i \n",n);
    return aire2;
}

void displayResult(float a, float b, int n, float aire){
    printf("L'intégrale de bornes %g, %g \n subdivisé par n = %i \n est égale à %g \n\n", a, b, n, aire);
}

float f(float x){
    return( exp(sin(5*x)) );
}

float simpson(float a, float b, int n){
    float aire; /* La réponse */
    float h = 1; /* pas de discritisation */
    float x, sum1, sum2; /* pour la sommation */
    h = (b-a)/n;
    x = a; sum1 = 0; sum2 = 0;

    for (int i = 0; i < n; i++)
    {
        sum2 += f((x + (x+h))/2);   /* x[i+(1/2)] = (x[i] + x[i+1])/2 */
        if(i >= 1){
            sum1 += f(x);
        }
        x+=h;
    }
    aire = (h/6) * (f(a) + (2*sum1) + (4*sum2) + f(b));
    return aire;
}