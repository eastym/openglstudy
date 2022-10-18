CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = rubber

LIBS =  -lglut -lGLU -lGL

OBJS = rubber.cpp

ARG = rubber

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./rubber $(ARG)

clean:; rm -f *.o *~ $(PROGRAM)