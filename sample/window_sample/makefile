CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = window

LIBS =  -lglut -lGLU -lGL

OBJS = window.cpp

ARG = window

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)			 
			./window ${ARG}

clean:; rm -f *.o *~ $(PROGRAM)