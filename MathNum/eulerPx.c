#include "stdio.h"
#include "stdlib.h"

float resolve(float* coef, float x, int t);

void DisplayResult(float* coef, float x, float px, int taille);

void getData(int* degre, int* taille,float** coef, float* x);

int main(){
    printf("(Polynome) Schema d'Hörner: \n");

///Initialisation
    float* coef; float x; int degre; int taille;

///Entrée des données
    getData(&degre, &taille, &coef, &x);

//Traitement
    float val = resolve(coef, x, taille-1);

//printf("La réponse du polynome p(x): \n %g", val);
    DisplayResult(coef, x, val, taille);
    free(coef);
    

    return 0;

}



void DisplayResult(float* coef, float x, float px, int taille){
    printf("le polynome P(%g)",x);
    for (int i = 0; i < taille; i++)
    {
        printf("a%i = %g; ", i, coef[i]);
    }
    printf("\n pour x = %g", x);
    printf("\n p(%g) = %f", x, px);
    printf("%lo", sizeof(long));
}

void getData(int* degre, int* taille,float** coef, float* x){
    *degre = 5;
    *taille = *degre + 1;
    float* newCoef = malloc(sizeof(float) * *taille);
    newCoef[0]= -1; newCoef[1]= 3; newCoef[2]=0; newCoef[3]=-1; newCoef[4]=0; newCoef[5]=2;
    *coef = newCoef;
    *x = 80;

}

/// Résolution par le schéma d'Euler
float resolve(float* coef, float x, int t){

    float val=coef[t]*x + coef[t-1];
    for (int i = t-2; i >= 0; i--){
        val = (val * x) + coef[i]; 
    }
    return val;
    
}