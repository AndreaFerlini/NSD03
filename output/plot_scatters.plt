#!/usr/bin/gnuplot -persist

set terminal png size 1200,900 enhanced font "Helvetica" 14

#set term postscript eps enhanced color "Helvetica" 18 dl 3

set logscale x
set logscale y

#set xtics 7e-8,10e-8,20e-5

#set ytics 1

set format x "10^{%L}";
set format y "10^{%L}";

#set xrange [50e-9:10e-3] 
#set yrange [50e-9:10e-3]

#set label "7e-10" at 70e-9
 
set key bmargin center horizontal nobox
set style line 2 lc rgb 'red' pt 2   # circle

set grid y
set grid x
 
set xlabel "PageRank ({/Symbol a}=0.15)"
set ylabel "InDegree"
set output "pr-in_deg.plot.png"
plot "pr-in_deg.out" with points pointtype 2 notitle

set xlabel "PageRank ({/Symbol a}=0.15)"
set ylabel "OutDegree"
set output "pr-out_deg.plot.png"
plot "pr-out_deg.out" with points pointtype 2 notitle


#set xlabel "PageRank ({/Symbol a}=0.15)"
#set ylabel "PageRank ({/Symbol a}=0.1)"
#set output "pr015-pr01.plot.png"
#plot "pr015-pr01.out" with points pointtype 2 notitle

#set xlabel "PageRank ({/Symbol a}=0.15)"
#set ylabel "PageRank ({/Symbol a}=0.2)"
#set output "pr015-pr02.plot.png"
#plot "pr015-pr02.out" with points pointtype 2 notitle

#set xlabel "PageRank ({/Symbol a}=0.15)"
#set ylabel "PageRank ({/Symbol a}=0.5)"
#set output "pr015-pr05.plot.png"
#plot "pr015-pr05.out" with points pointtype 2 notitle

#set xlabel "PageRank ({/Symbol a}=0.15)"
#set ylabel "PageRank ({/Symbol a}=0.9)"
#set output "pr015-pr09.plot.png"
#plot "pr015-pr09.out" with points pointtype 2 notitle
