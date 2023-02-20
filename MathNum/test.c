#include <stdio.h> 
#include <math.h>

double f(double x);
void limiteDarret(double* eps, double* a, double* b, double* n);
double absolute(double n);
double trapeze(double* a, double* b, double* n);

int main(int argc, char const *argv[])
{
    printf("Calcule d'intégration par méthode de trapèze: \n\n");

//Initialisation
    double val = -1;
    double a, b;            //Bornes de l'intégration
    double n = 1.28;

//Entrée des valeurs
    a = 0; b = 1;           //Bornes de l'intégration
    double epsilone = 1e-8;

//Traitement 
    limiteDarret(&epsilone , &a, &b, &n);
    val = trapeze(&a, &b, &n);
    printf("L'intégral de borne a = %g et b = %g\n, Limite d'arrêt n = %g\n, L'intégrale est égale à  %g\n\n", a, b, n, val);
    
    return 0;
}

/*double f(double x){
    return 1 / (8-pow(x,3));
}*/

double f(double x){
     return exp(sin(5*x));
}

double absolute(double n){
    return (n < 0) ? -1*n : n;
}

void limiteDarret(double* eps, double* a, double* b, double* n){
    double In = 0;
    double In1 = 10;
    *n = 2;
    while (absolute(In1-In) >= *eps)
    {
        /* code */
        In =  (((*b - *a) / *n) / 2) * (f(*a + (*n + 1) * ((*b - *a) / *n)) -f(*a + *n * (*b - *a) / *n));
        In1 = (((*b - *a) / (*n + 1)) / 2) * (f(*a + (*n + 2) * ((*b - *a) / (*n + 1))) -f(*a + (*n + 1) * (*b - *a) / (*n + 1)));
        *n += 1;
    }
}
double trapeze(double* a, double* b, double* n){
    double somme = 0;
    double h = ((*b - *a) / *n);
    for (int i = 1; i < *n; i++)
    {
        /* code */
        somme += f(*a + i * h);
    }
    return (h/2) * (f(*a) + 2 * somme + f(*b));
    
}

