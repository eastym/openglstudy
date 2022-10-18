CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = size

LIBS =  -lglut -lGLU -lGL

OBJS = size.cpp

ARG = size

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)			 
			./size ${ARG}

clean:; rm -f *.o *~ $(PROGRAM)