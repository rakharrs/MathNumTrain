#include <stdio.h>
#include <math.h>

void displayResult(float a, float b, float x);
float f(float x);
float fprime(float x);
float newton(float a, float b, float eps);
float dichotomie(float a, float b, float eps);
void selectChoice(int choice, float* a, float* b, float eps, float* x, int* done);
void changeIntervalle(float* a, float* b);

int main(){
    printf("Resolution de l'équation (x-2-ln(x)) : \n");
/// Données - entrée
    float a = 0.2;       float b = 1;
    float eps = 1e-6;     float x = 0;

/// Traitement
    x = newton(a, b, eps);
    int done = 0;
    int choice = 0;
    printf("omsqfdgjmlqfdjg %f\n",f(0.352288f));

    while (!done) {
        printf("0:  change intervalle \n");
        printf("1:  Résoudre par méthode de Bissection \n");
        printf("2:  Résoudre par méthode de Newton \n");
        
        scanf("%i", &choice);
        selectChoice(choice, &a, &b, eps, &x, &done);
    }
    displayResult(a, b, x);

/// Sortie
    displayResult(a, b, x);
    return 0;
}

void displayResult(float a, float b, float x){
    printf("La résolution de f dans l'intervalle [%g,%g] est: \n \t\t x = %g", a, b , x);
}

float f(float x){
    return (sin(2*x)-1+x);
}

float fprime(float x){
    return (2*cos(2*x) + 1);
}

float newton(float a, float b, float eps){
    float x0 = a; float x1 = 0;
    x1 = x0 - (f(x0)/fprime(x0));
    if((x1 - a)*(x1 - b) > 0){
        x0 = b;
        x1 = b - (f(b)/fprime(b));
    } 
    while(fabs((x1-x0)) > eps){
        x0 = x1;
        x1 = x0 - (f(x0)/fprime(x0));
        printf("xn = %g \n",x1);
    }

    return x1;
}

float dichotomie(float a, float b, float eps){
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


void selectChoice(int choice, float* a, float* b, float eps, float* x, int* done){
    *done = 1;
    switch (choice)
    {
    case 0:     //Modifier l'intervalle
        changeIntervalle(a, b);
        *done = 0;
        break;

    case 1:     //Méthode de bissection
        *x = dichotomie(*a, *b, eps);
        break;

    case 2:     //Méthode de Newton
        *x = newton(*a, *b, eps);
        break;

    default:
        printf("no choice");
        break;
    }
    
}

void changeIntervalle(float* a, float* b){
    printf("La valeur de a: \n");
    scanf("%g",a);
    
    printf("\nLa valeur de b: \n");
    scanf("%g",b);

    printf("\n L'intervalle a été changé en [%g,%g] \n",*a, *b);
}