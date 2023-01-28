
testapp:	testapp.o avl.o
	g++ -o testapp testapp.o avl.o

testapp.o:	avl.h testapp.cpp
	g++ -c testapp.cpp

avl.o:	avl.h avl.cpp
	g++ -c avl.cpp

