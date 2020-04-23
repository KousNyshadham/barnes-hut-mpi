nbody: main.o quadtree.o body.o quad.o
	g++ main.o quadtree.o body.o quad.o -o nbody

main.o: main.cpp
	g++ -c main.cpp

quadtree.o: quadtree.cpp quadtree.h
	g++ -c quadtree.cpp

quad.o: quad.cpp quad.h
	g++ -c quad.cpp

body.o: body.cpp body.h
	g++ -c body.cpp

clean:
	rm *.o nbody