CC = g++

CFLAGS = -Wall -Weffc++ -g

PROGRAM = teapot

LIBS =  -lglut -lGLU -lGL

OBJS = teapot.cpp

ARG = teapot

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)


run: $(PROGRAM)
			./teapot $(ARG)
			

clean:; rm -f *.o *~ $(PROGRAM)