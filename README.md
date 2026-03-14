Usage:    
./a.out 0 5 5 6 plot_data.txt

gnuplot -p -e "plot 'plot_data.txt' using 1:2 with lines title 'Exact', '' using 1:3 with lines title 'Approx'"
          
  или скриптом:
  
  make
              
  chmod +x run_and_plot.sh
              
  ./run_and_plot.sh 0 2 1000 2 plot_data.txt
