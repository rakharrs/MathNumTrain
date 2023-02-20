#Standard 2D plot commands for gnuplot
reset
#Optional labels
set title "Deix belles coirnes"
set xlabel "Temps\nen secondes"
set ylabel "Mesures"
set key top left
set key box
set tics out

# Autorange otherwise; 
set xrange[0:6]
set yrange[-2:2]

# Second Y-Axis
set y2label "Autre mesure"
set y2range [1:500]
set y2tics
set logscale xy
unset log y
unset log x
set log y2
set grid x y2
#set autoscale y2

set xzeroaxis linetype 0 linewidth 2
set yzeroaxis linetype 0 linewidth 2

# Plot 2 curves
set datafile separator ","
plot "mesure.txt" with linespoints linetype 3 linewidth 2, \
	sin(3*x)/(3*x) with lines linetype 1 linewidth 1
