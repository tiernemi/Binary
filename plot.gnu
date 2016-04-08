set title "Plot Of Search Duration Vs Binary Tree Size For Ordered And Random Insert Regimes"
set xlabel "Tree Size"
set ylabel "Duration (ms)"
set logscale y
set key left

plot "bench.dat" using 1:2 title "Random", "bench.dat" using 1:3 title "Ordered"
