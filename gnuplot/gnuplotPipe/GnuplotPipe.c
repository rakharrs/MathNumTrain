#include <stdio.h>

int main(){
    printf("Open a pipe to gnuplot \n");
    FILE *gnuplotPipe = popen("/opt/homebrew/bin/gnuplot -persist", "w");
    if (gnuplotPipe){
        fprintf(gnuplotPipe, "set terminal qt size 800,600 \n");
        fprintf(gnuplotPipe, "set title 'Resultat de mesures et sin(x)' \n");
        fprintf(gnuplotPipe, "set xlabel 'Temps (s)' \n");
        fprintf(gnuplotPipe, "set ylabel 'Valeurs' \n");
        fprintf(gnuplotPipe, "set yrange [-1.5:2]\n");
        fprintf(gnuplotPipe, "set style data linespoints \n");

        //fprintf(gnuplotPipe, "set loadpath \"/Users/rakotoharisoa/Documents/Workspace/C/gnuplot\" \n");
        fprintf(gnuplotPipe, "load 'graph1.plt' \n");

        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    }else{
        printf("Gnuplot not found");
    }
    return 0;
}