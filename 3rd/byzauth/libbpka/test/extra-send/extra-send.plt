

set terminal postscript
set output 'extra-send.ps'
set xrange [30:50]
set yrange [0:140]
#set key bottom left 

set size 0.6,0.6
set xlabel 'Day of Year'
set ylabel 'Percentage of Peers Authenticated'

plot \
     'completion.3600.dat' using ($1/86400):2 with lines title 'Check emails every hour' , \
     'completion.86400.dat' using ($1/86400):2 with lines title 'Check emails every day'  , \
     'completion.604800.dat' using ($1/86400):2 with lines title 'Check emails every week' , \
     'completion.base.dat' using ($1/86400):2 with lines title 'Baseline lazy protocol' 
