#!/bin/bash
./a.out "$@"   # передаём все аргументы вашей программе
if [ -f plot_data.txt ]; then
    gnuplot plot.plt
else
    echo "Файл plot_data.txt не найден. Убедитесь, что программа создала его."
fi