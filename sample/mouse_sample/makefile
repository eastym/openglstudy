CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = mouse

LIBS =  -lglut -lGLU -lGL

OBJS = mouse.cpp

ARG = mouse

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			./mouse ARG

clean:; rm -f *.o *~ $(PROGRAM)