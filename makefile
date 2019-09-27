CC = g++
CFLAGS = -g
TARGET = statSem
OBJS = main.o scanner.o parser.o nodet.o testtree.o semantic.o
DEPS = scanner.h token.h parser.h nodet.h testtree.h semantic.h

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) 

main.o: main.cpp parser.h testtree.h semantic.h
	$(CC) $(CFLAGS) -c main.cpp 

parser.o: parser.cpp token.h scanner.h parser.h nodet.h
	$(CC) $(CFLAGS) -c parser.cpp 

scanner.o: scanner.cpp token.h
	$(CC) $(CFLAGS) -c scanner.cpp 

nodet.o: nodet.cpp nodet.h
	$(CC) $(CFLAGS) -c nodet.cpp

testtree.o: testtree.cpp nodet.h
	$(CC) $(CFLAGS) -c testtree.cpp

semantic.o: semantic.cpp semantic.h
	$(CC) $(CFLAGS) -c semantic.cpp

clean:
	/bin/rm -f *.o $(TARGET)
