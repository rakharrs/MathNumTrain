#include <stdio.h>
#include <stdlib.h>

float **newMat(int dim){
    float** A = NULL;
    A = malloc(dim*sizeof(float*));
    if(A==NULL) problem("ne peut pallouer une matrice");

    for(int i = 0; i<dim; i++){
        A[i] = malloc(dim*sizeof(float));
        if(A[i] == NULL) problem("ne peut allouer une ligne de matrice");
    }
    return A;
}

void problem(char* message){
    printf("%s\n", message);
    exit(2);
}

float* newVect(int dim){
    float* v = NULL;
    v = malloc(dim*sizeof(float));
    if(v==NULL) provlem("Ne peut allouer un vecteur");
    return v;
}

float** triangularisation(float** a, float* b, int taille){
    int n = taille;

    for (int k = 0; k <= n-2; k++)
    {
        for (int i = k+1; i <= n-1; i++)
        {
            for (int j = k+1; j <= n-1 ; j++)
            {
                float t = a[i][j] - ((a[i][k]/a[k][k])*a[k][j]);
                a[i][j] = t;
            }
            b[i] = b[i] - ((a[i][k]/a[k][k]) * b[k]);
            a[i][k] = 0;
            
        }
        
    }
    

}