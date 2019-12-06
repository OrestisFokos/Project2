CC = g++ -std=c++11 -g

default:lsh
lsh: file.o brute_force.o calculations.o ann.o range_search.o hashTable.o hypercube.o initialization.o assignment.o main.o
	$(CC) -o lsh file.o brute_force.o calculations.o hashTable.o hypercube.o ann.o range_search.o initialization.o assignment.o main.o

file.o: file.cpp file.h brute_force.h hashTable.h calculations.h
	$(CC) -c file.cpp

brute_force.o: brute_force.cpp brute_force.h
	$(CC) -c brute_force.cpp

calculations.o: calculations.cpp calculations.h
	$(CC) -c calculations.cpp

ann.o: ann.cpp ann.h hashTable.h calculations.h brute_force.h
	$(CC) -c ann.cpp

range_search.o: range_search.cpp hashTable.h calculations.h brute_force.h
	$(CC) -c range_search.cpp

hashTable.o: hashTable.cpp hashTable.h calculations.h
	$(CC) -c hashTable.cpp

random_initialization.o: initialization.cpp initialization.h file.h
	$(CC) -c initialization.cpp

assignment.o: assignment.cpp assignment.h calculations.h file.h
	$(CC) -c assignment.cpp

hypercube.o: hypercube.cpp hypercube.h
	$(CC) -c hypercube.cpp

main.o: main.cpp calculations.h hashTable.h hypercube.h brute_force.h file.h ann.h initialization.h
	$(CC) -c main.cpp

clean:
	$(RM) count *.o *~
