CC = g++
CFLAGS = -Wall -c -g 
OFLAGS = -o
BIN = ../bin/
INCLUDE = -I../include/
HEADER = ../include/
SRC = ../src/
OBJ = ../obj/
MODEL = ../model/
LIB = ../lib/

all: $(LIB)lib_heaptracker.a $(OBJ)main.o
	$(CC) $(OFLAGS) main $(OBJ)main.o -L. $(LIB)lib_heaptracker.a
	mv main $(BIN)

$(OBJ)main.o: ../main.cpp $(HEADER)heaptracker.h
	$(CC) $(CFLAGS) ../main.cpp $(INCLUDE)
	mv main.o $(OBJ)


$(LIB)lib_heaptracker.a: $(OBJ)lib_trackAlloc.o $(OBJ)lib_trackDealloc.o $(OBJ)lib_track.o $(OBJ)lib_LinkedList.o $(OBJ)lib_Alloc.o $(OBJ)lib_Dealloc.o
	ar rcs lib_heaptracker.a $(OBJ)lib_trackAlloc.o $(OBJ)lib_trackDealloc.o $(OBJ)lib_track.o $(OBJ)lib_LinkedList.o $(OBJ)lib_Alloc.o $(OBJ)lib_Dealloc.o
	mv lib_heaptracker.a $(LIB)

$(OBJ)lib_trackAlloc.o: $(SRC)trackAlloc.cpp 
	$(CC) $(CFLAGS) $(SRC)trackAlloc.cpp $(OFLAGS) $(OBJ)lib_trackAlloc.o
	
$(OBJ)lib_trackDealloc.o: $(SRC)trackDealloc.cpp 
	$(CC) $(CFLAGS) $(SRC)trackDealloc.cpp  $(OFLAGS) $(OBJ)lib_trackDealloc.o
	
$(OBJ)lib_track.o: $(SRC)track.cpp
	$(CC) $(CFLAGS) $(SRC)track.cpp $(OFLAGS) $(OBJ)lib_track.o

$(OBJ)lib_LinkedList.o: $(SRC)LinkedList.cpp
	$(CC) $(CFLAGS) $(SRC)LinkedList.cpp $(OFLAGS) $(OBJ)lib_LinkedList.o

$(OBJ)lib_Alloc.o: $(MODEL)Alloc.cpp
	$(CC) $(CFLAGS) $(MODEL)Alloc.cpp $(OFLAGS) $(OBJ)lib_Alloc.o

$(OBJ)lib_Dealloc.o: $(MODEL)Dealloc.cpp
	$(CC) $(CFLAGS) $(MODEL)Dealloc.cpp $(OFLAGS) $(OBJ)lib_Dealloc.o

clean: 
	rm -f $(LIB)lib_heaptracker.a
	rm -f $(OBJ)*.o 
	rm -f $(BIN)*

