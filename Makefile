all: main.o task1.o func.o error.o
	g++ main.o task1.o func.o error.o

main.o: main.cpp task1.h func.h error.h
	g++ -Wall -std=c++20 -O3 -c main.cpp

task1.o: task1.cpp task1.h
	g++ -Wall -std=c++20 -O3 -c task1.cpp

func.o: func.cpp func.h
	g++ -Wall -std=c++20 -O3 -c func.cpp

error.o: error.cpp error.h task1.h func.h
	g++ -Wall -std=c++20 -O3 -c error.cpp

clean:
	rm -f *.o *.out
