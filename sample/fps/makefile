CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = fps

LIBS =  -lglut -lGLU -lGL

OBJS = test.cpp

ARG = drag

DEFAULT = 60

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./fps $(DEFAULT)

run-%: $(PROGRAM)
			./fps ${@:run-%=%}

clean:; rm -f *.o *~ $(PROGRAM)