nbody: main.o quadtree.o body.o quad.o
	mpicxx --std=c++11 main.o quadtree.o body.o quad.o -o nbody

main.o: main.cpp
	mpicxx --std=c++11 -c main.cpp

quadtree.o: quadtree.cpp quadtree.h
	mpicxx --std=c++11 -c quadtree.cpp

quad.o: quad.cpp quad.h
	mpicxx --std=c++11 -c quad.cpp

body.o: body.cpp body.h
	mpicxx --std=c++11 -c body.cpp

clean:
	rm *.o nbody
