all: main.o task1.o func.o
	g++ main.o task1.o func.o

main.o: main.cpp task1.h func.h
	g++ -Wall -std=c++20 -O3 -c main.cpp

task1.o: task1.cpp task1.h
	g++ -Wall -std=c++20 -O3 -c task1.cpp

func.o: func.cpp func.h
	g++ -Wall -std=c++20 -O3 -c func.cpp

clean:
	rm -f *.o *.out
