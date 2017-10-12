#!/usr/bin/gnuplot -persist
set terminal png size 1200,900 enhanced font "Helvetica" 14

set xlabel "Iterations"
set ylabel "Pagerank Values"
#set logscale x
#set logscale y
#set xtics 1
#set ytics 1
#set xrange [1:50] 
#set yrange [5e-8:2e-7]
 
set key bmargin center horizontal nobox
set style line 2 lc rgb 'red' pt 15   # circle
set grid y
 
set output "convergence.plot.png"
 
plot "convergence_plot.txt" using 1:2 every 10::1 with lines smooth csplines title '572',\
    "convergence_plot.txt" using 1:2 every 10::2 with lines smooth csplines title '1252',\
    "convergence_plot.txt" using 1:2 every 10::3 with lines smooth csplines title '2296',\
    "convergence_plot.txt" using 1:2 every 10::4 with lines smooth csplines title '4218',\
    "convergence_plot.txt" using 1:2 every 10::5 with lines smooth csplines title '9405',\
    "convergence_plot.txt" using 1:2 every 10::6 with lines smooth csplines title '11616',\
    "convergence_plot.txt" using 1:2 every 10::7 with lines smooth csplines title '17168',\
    "convergence_plot.txt" using 1:2 every 10::8 with lines smooth csplines title '18628',\
    "convergence_plot.txt" using 1:2 every 10::9 with lines smooth csplines title '23424',\
    "convergence_plot.txt" using 1:2 every 10::10 with lines smooth csplines title '26975'
