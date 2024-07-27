main: main.o item.o knapsack.o simulated_annealing.o
	g++ main.o item.o knapsack.o simulated_annealing.o -o main 

main.o: main.cp
	g++ -c main.cp
	
item.o: item.c
	g++ -c item.cpp

knapsack.o: knapsack.cpp
	g++ -c knapsack.cpp

simulated_annealing.o: simulated_annealing.cpp
	g++ -c simulated_annealing.cpp

clean:
	rm *.o main