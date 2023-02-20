#include <stdio.h>
#include <math.h>

float newton(float initial, float n);
float f(float x, float y);
float g(float z, float y, float x, float h);

int main() {
/// Donnée
    float initial = 2;
    int n = 0;
    float x = n / 10;
    float y = 2;

/// Traitement
    FILE* file = fopen("graphe.txt", "w");
    fprintf(file, "%g %g\n", x, y);
    for (n = 1; n <= 20; n++) {
        x = n / 10.0;
        y = newton(y, n);
        fprintf(file, "%g %g\n", x, y);
    }
    fclose(file);

/// Sortie
    FILE* gnuplot = popen("/opt/homebrew/bin/gnuplot -persist", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'graphe.txt' w l, (exp(-x)/3)*(5*exp(-x*x*x)+1)\n");
        fflush(gnuplot);
        fclose(gnuplot);
    } else printf("Gnuplot not found");
    return 0;
}

float newton(float initial, float n) {
    float h = 0.05;
    float epsilone = 1e-6;
    float x = n * h;
    float z0 = initial;
    float z1 = z0 + ((h * f(x, z0)) / (1 + h * (3 * x * x + 1)));
    while (fabs(z1 - z0) > epsilone) {
        z0 = z1;
        z1 = z0 - (g(z0, initial, x, h) / (1 + h * (3 * x * x + 1)));
    }
    return z1;
}

float g(float z, float y, float x, float h) {
    return z - y - h * f(x, z);
}

float f(float x, float y) {
    return x * x * exp(-x) - (3 * x * x + 1) * y;
}