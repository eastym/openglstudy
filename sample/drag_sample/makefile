CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = drag

LIBS =  -lglut -lGLU -lGL

OBJS = drag.cpp

ARG = drag

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./drag ARG

clean:; rm -f *.o *~ $(PROGRAM)