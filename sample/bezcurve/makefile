CC = g++

CFLAGS = -Wall -Weffc++ -g

PROGRAM = bezcurve

LIBS =  -lglut -lGLU -lGL

OBJS = bezcurve.cpp

ARG = bezcurve

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
			 $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)


run: $(PROGRAM)
			./bezcurve $(ARG)
			

clean:; rm -f *.o *~ $(PROGRAM)