CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = solid

LIBS =  -lglut -lGLU -lGL

OBJS = solid.cpp

ARG = solid

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./solid $(ARG)

clean:; rm -f *.o *~ $(PROGRAM)