CC = g++

CFLAGS = -Wall -Weffc++

PROGRAM = line

LIBS =  -lglut -lGLU -lGL

OBJS = line.cpp

ARG = line

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) -Dold $(OBJS) $(LIBS) -o $(PROGRAM)

new:  $(OBJS)
			 $(CC) -Dnew $(OBJS) $(LIBS) -o $(PROGRAM)
run: $(PROGRAM)
			./line $(ARG)

clean:; rm -f *.o *~ $(PROGRAM)