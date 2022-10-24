CC = g++

CFLAGS =  -Wall -Weffc++ -g -std=c++20

PROGRAM = animation

LIBS =  -lglut -lGLU -lGL

OBJS = animation.cpp display.cpp

ARG = animation

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)


run: $(PROGRAM)
			./animation 
			

clean:; rm -f *.o *~ $(PROGRAM)