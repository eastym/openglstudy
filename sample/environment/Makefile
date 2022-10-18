CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = environment

LIBS =  -lglut -lGLU -lGL

OBJS = environment.cpp

ARG = environment

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./environment ARG

clean:; rm -f *.o *~ $(PROGRAM)