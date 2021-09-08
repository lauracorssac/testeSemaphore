main:
	g++ -std=c++11 -c texte.cpp
	g++ -o aa texte.o -lpthread
	./aa

original:
	g++ -std=c++11 -c original.cpp
	g++ -o original original.o
	./original

bufferAndClass:
	g++ -std=c++11 -c bufferAndClass.cpp
	g++ -o bufferAndClass bufferAndClass.o  -lpthread
	./bufferAndClass
