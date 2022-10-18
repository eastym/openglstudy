CC = g++

CFLAGS = -Wall -Weffc++ -g

PROGRAM = cube

LIBS =  -lglut -lGLU -lGL

OBJS = cube.cpp

ARG = cube

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)


run: $(PROGRAM)
			./cube $(ARG)
			

clean:; rm -f *.o *~ $(PROGRAM)