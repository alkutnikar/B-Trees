

set terminal jpeg

set output "bplus.jpg"

set title "B+ Insert"
set xlabel "no. of elements"
set ylabel "time in seconds"

set xrange [0:80000]
set yrange [0:0.1]
set xtics 10000
set ytics 0.01

plot "bplus.txt" with linespoints 1 1

