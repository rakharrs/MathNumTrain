#include "stdio.h"
#include "math.h"

float f(float x);
void displayResult(float a, float b, float aire);
float simpson(float a, float b, int n);

int main(){
    printf("<< Intégration par méthode de Simpson >> \n \n");
/// Initialisation
    float a, b;             // Bornes d'intégration
    float aire;

/// Entrée des données
    a = 0; b = 1; aire = 777;

/// Traitement


/// Sortie
    displayResult(a,b,aire);
    return 0;
}

/// Fonction exp(sin(5*x))
float f(float x){ 
    return exp(sin(5*x));
}

void displayResult(float a, float b, float aire){
    printf("L'intégrale de f entre ses bornes a = %g et b = %g  \n",a,b);
    printf("est : %g \n",aire);
}

float simpson(float a, float b, int n){
    float h = (b - a)/n;    // pas de discrétisation
    float s1 = 0;            // Pour la première sommation 
    float s2 = 0;            // Pour la deuxieme sommation
    float x1 = 0;
    float x2 = 0;
    for (int i = 0; i < n; i++)
    {
        
        if(i >= 1) x1+=h ;s1 += f(x);
        
    }
    
}