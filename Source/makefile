all: esv7

esv7: main.o Entity.o glEntity.o DataFile.o
	g++ -L/usr/include/GL -lGL -lglut -lGLU main.o Entity.o glEntity.o DataFile.o -o esv7

main.o: main.cpp
	g++ -c main.cpp

Entity.o: Entity.cpp Entity.h
	g++ -c Entity.cpp

glEntity.o: glEntity.cpp glEntity.h
	g++ -c glEntity.cpp

DataFile.o: DataFile.cpp DataFile.h
	g++ -c DataFile.cpp

clean:
	rm -rf *o esv7
