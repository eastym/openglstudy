CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = moving

LIBS =  -lglut -lGLU -lGL -lglfw -lGLEW

OBJS = moving.cpp

ARG = moving

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

run: $(PROGRAM)
			 ./moving  $(ARG)

clean:; rm -f *.o *~ $(PROGRAM)