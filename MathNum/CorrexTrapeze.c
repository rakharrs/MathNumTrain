#include "stdio.h"
#include "math.h"

float f(float x);
void display(float a, float b, float aire);
float Trapeze(float a, float b, int n);
float integrate(float a, float b, float eps);

int main(){
    printf("<< Intégration par méthode de trapèze >> \n \n");

// Initialisation
    float a = 0, b = 0;         ///Bornes d'intégrations
    float aire = 0;
    int n = 2500;

// Entrée des données
    n = 250;
    a = 0; b = 1;                  ///Bornes d'intégrations

// Traitement
    aire = integrate(a, b, 1e-6);


// Sortie
    display(a,b,aire);
    return 0;
}

float f(float x){
    return( exp(sin(5*x)) );
}

void display(float a, float b, float aire){
    printf("L'intégrale de f entre %g et %g est :\n",a,b);
    printf("%g", aire);
}

float Trapeze(float a, float b, int n){
    float aire = 675;
    float sum = 0;                  //Pour la sommation
    float h = 1;                    //pas de discrétisation
    float x = 0;

    x = a;
    h = (b-a)/n;

    for (int i = 1; i < n; i++)
    {
        x += h;
        sum += f(x);
    }
    aire = h/2 * (f(a) + 2 * sum + f(b));
    return aire;
    
}

float integrate(float a, float b, float eps){
    float aire = 0;
    int n =10;
    float aire1 = 0, aire2 = 1;
    aire1 = Trapeze(a, b, n);
    n+=10;
    aire2 = Trapeze(a, b, n);
    while(fabs(aire1 - aire2) > eps){
        aire1 = aire2;
        n+=10;
        aire2 = Trapeze(a,b,n);
    }
    printf("La valeur de n recuperee est : %g \n",n);
    return aire2;
}