set terminal png size 1600,900 enhanced font 'Arial,12'
set output 'algorithm_comparison_plot.png'
set multiplot layout 2,2

set title 'Algorithm Comparison: Growth Rates Matter!' font 'Arial,14'
set xlabel 'Input Size (n)' font 'Arial,12'
set ylabel 'Time (milliseconds)' font 'Arial,12'
set grid
set key left top
plot 'algorithm_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1 lc rgb '#2ECC71' title 'Linear Search O(n)', \
     'algorithm_data.txt' using 1:3 with linespoints lw 2 pt 9 ps 1 lc rgb '#3498DB' title 'Sort O(n log n)', \
     'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1 lc rgb '#F39C12' title 'Bubble Sort O(n^2)'

set title 'Fast Algorithms: O(n) vs O(n log n)' font 'Arial,13'
set xlabel 'Input Size (n)' font 'Arial,11'
set ylabel 'Time (ms)' font 'Arial,11'
set grid
set key left top
plot 'algorithm_data.txt' using 1:2 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#2ECC71' title 'Linear Search O(n)', \
     'algorithm_data.txt' using 1:3 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#3498DB' title 'Sort O(n log n)'

set title 'Bubble Sort: O(n^2) - Why It Gets Slow' font 'Arial,13'
set xlabel 'Input Size (n)' font 'Arial,11'
set ylabel 'Time (ms)' font 'Arial,11'
set grid
unset key
plot 'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1.2 lc rgb '#F39C12'

set title 'Log-Log Plot: Identifying Complexity' font 'Arial,13'
set xlabel 'log(Input Size)' font 'Arial,11'
set ylabel 'log(Time)' font 'Arial,11'
set logscale xy
set grid
set key left top
plot 'algorithm_data.txt' using 1:($2 > 0 ? $2 : 1/0) with linespoints lw 2 pt 7 ps 1 lc rgb '#2ECC71' title 'Linear O(n)', \
     'algorithm_data.txt' using 1:($3 > 0 ? $3 : 1/0) with linespoints lw 2 pt 9 ps 1 lc rgb '#3498DB' title 'Sort O(n log n)', \
     'algorithm_data.txt' using 1:($4 > 0 ? $4 : 1/0) with linespoints lw 2 pt 11 ps 1 lc rgb '#F39C12' title 'Bubble O(n^2)'

unset multiplot
