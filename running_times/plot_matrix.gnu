set terminal png size 1200,600 enhanced font 'Arial,12'
set output 'matrix_plot.png'
set multiplot layout 1,2

set title 'Matrix Multiplication: Running Time vs Input Size' font 'Arial,14'
set xlabel 'Matrix Size (n)' font 'Arial,12'
set ylabel 'Time (milliseconds)' font 'Arial,12'
set grid
set key left top
plot 'matrix_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb '#16A085' title 'Measured Time'

set title 'Measured vs Theoretical O(n^3)' font 'Arial,14'
set xlabel 'Matrix Size (n)' font 'Arial,12'
set ylabel 'Time (milliseconds)' font 'Arial,12'
set grid
set key left top
plot 'matrix_data.txt' using 1:2 with points pt 7 ps 1.5 lc rgb '#16A085' title 'Measured Time', \
     'theory_data.txt' using 1:2 with lines lw 2 dt 2 lc rgb '#FF6B9D' title 'O(n^3) fit: 1.107227e-06 * n^3'

unset multiplot
