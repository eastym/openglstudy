CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = glut_main

LIBS =  -lglut -lGLU -lGL

OBJS = mi.cpp

ARG = main

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)			 
			./glut_main ${ARG}

clean:; rm -f *.o *~ $(PROGRAM)
