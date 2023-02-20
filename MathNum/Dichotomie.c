#include <stdio.h>
#include <math.h>

void displayResult(float a, float b, float x);
float f(float x);
float resolve(float a, float b, float eps);

int main(){
    printf("Résolution d'une équation linéaire par la méthode de dichotomie:  \n");

/// Données
    float a = 34.9;
    float b = 90.7;
    float eps = 77.7;
    float x = 8;

/// Entrée des données
    eps = 1e-6;
    a = 0.1;
    b = 1;

/// Traitement
    x = resolve(a, b, eps);

/// Sortie de résultat
    displayResult(a, b, x);
    return 0;
}

void displayResult(float a, float b, float x){
    printf("La racine de f entre les bornes %g; %g est: \n %g", a, b, x);
}

float f(float x){
    return (x - 2 - log(x));
}

/// Résolution par méthode de bisection (dichotomie)
float resolve(float a, float b, float eps){
    float x = 1.0;
    while(fabs(b-a)>eps){
        x=(a+b)/2;
        if(f(a)*f(x) < 0){
            b = x;

        } 
        else a = x;
    }
    return x;
}