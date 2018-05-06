bestRental: main.o Helper.o
	g++ main.o Helper.o -o bestRental
main.o: main.cc Helper.h
	g++ -c main.cc
Helper.o: Helper.cc Helper.h LinkedList.h
	g++ -c Helper.cc
clean:
	rm *.o *~ bestRental
