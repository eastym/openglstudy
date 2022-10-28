CC = g++

CFLAGS = -g -std=c++20

PROGRAM = animation

LIBS =  -lglut -lGLU -lGL -lglfw

OBJS = animation.cpp display.cpp ../fps/fps.cpp

ARG = animation

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)


run: $(PROGRAM)
			./animation 
			

clean:; rm -f *.o *~ $(PROGRAM)