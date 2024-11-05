CC = g++
CFLAGS = --std=c++17 -Wall 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 
# Your .hpp files
DEPS = Sokoban.hpp
# Your compiled .o files
OBJECTS = Sokoban.o
# The name of your program
PROGRAM = Sokoban

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
Sokoban: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
Sokoban: Sokoban.a $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	
Sokoban.a: $(OBJECTS)
	ar rcs $@ $^
pname.a: $(OBJECTS)
	ar rcs $@ $^
clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp