CC = g++

CFLAGS = -Wall -Weffc++ -g -std=c++20

PROGRAM = walkthrough

LIBS =  -lglut -lGLU -lGL -lglfw -lGLEW

OBJS = walkthrough.cpp

ARG = walkthrough

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./walkthrough

clean:; rm -f *.o *~ $(PROGRAM)