nbody: main.o quadtree.o body.o quad.o
	g++ --std=c++11 main.o quadtree.o body.o quad.o -o nbody

main.o: main.cpp
	g++ --std=c++11 -c main.cpp

quadtree.o: quadtree.cpp quadtree.h
	g++ --std=c++11 -c quadtree.cpp

quad.o: quad.cpp quad.h
	g++ --std=c++11 -c quad.cpp

body.o: body.cpp body.h
	g++ --std=c++11 -c body.cpp

clean:
	rm *.o nbody