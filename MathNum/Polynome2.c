#include<stdio.h>
#include<stdlib.h>

void displayResult(float x, float* a, int n, float result);
int getChoice(float** a, int* degree, float* x, int choice);
float resolve(float* a, float x, int length);
void setPolynome(float** a, int* degree);

int main() {
    printf("Calcul de polynome\n");
/// Donnée
    int degree = 0;
    float* a = NULL;
    float x = 0;

/// Traitement
    int done = 0;
    int choice = 0;

    while (!done) {
        printf("1: Enter The coef  ");
        printf("2: Enter The degree  ");
        printf("3: Enter The polynome  ");
        printf("4: Calcul  \n ");
        printf("0: END\n");
        scanf("%i", &choice);
        done = getChoice(&a, &degree, &x, choice);
    }
/// Sorite
    // displayResult(x, a, degree);
    free(a);
    return 0;
}

void displayResult(float x, float* a, int n, float result) {
    printf("P(x) = %g*x^%i" , a[n-1], n-1);
    for (int i = n-2; i >= 0; i--)
        printf("+ %g*x^%i ", a[i], i);
    printf("\n");
    printf("\n");
    printf("P(%g) = %g\n", x, result);
}

int getChoice(float** a, int* degree, float* x, int choice) {
    switch (choice)
    {
    case 4: //Enter The degree
        if (*a!=NULL) {
            displayResult(*x, *a, *degree, resolve(*a, *x, *degree));
        } else {
            printf("NO POLYNOME\n");
        }
        break;
    case 3: //Enter The polynome
        if (*a!=NULL || *degree==0) {printf("Enter The degree for the polynome\n"); free(*a); break;}
        printf("3: The polynome is \n");
        setPolynome(a, degree);
        break;
    case 2: //Enter The degree
        if (*a!=NULL) free(*a);
        printf("2: The degree is ");
        scanf("%i", degree);
        break;
    
    case 1: //Enter le coefficiant
        printf("1: The coef is ");
        scanf("%f", x);
        break;
    default: //Arrêt du programme
        return 1;
        break;
    }
    return 0;
}

void setPolynome(float** a, int* degree) {
    float* coef = NULL;
    *degree += 1;
    coef = (float*)malloc(*degree*sizeof(float)); //Allocation avec decoupage en floatxf
    for (int i = *degree - 1; i >= 0; i--) {
        printf("a[%i] = ", i);
        scanf("%f", &coef[i]);
    }
    *a = coef;
}

float resolve(float* a, float x, int length) {
    float result = a[length-1]*x+a[length-2];
    for (int n = length-3; n >= 0; n--)
        result = result * x + a[n];
    return result;
}
