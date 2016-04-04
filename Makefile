CC=clang++
#CC=g++
CFLAGS+= -std=c++11 #-g -O0 -Wall -pedantic -I./ -I./include

#STRINGFIX = -lXext -lX11
STRINGFIX = -lXext -lX11 -L/usr/lib/nvidia-340-updates
GLUT2 = -lGL -lGLU -lglut -lpthread
GLUI2 = -L./src/lib -lglui
LIBS = $(STRINGFIX) $(GLUT2) $(GLUI2)

PROD= Demo

#HDRS= $(shell ls *.h)
SRCS= $(shell ls *.cpp)
SRCS+= $(shell ls ui/*.cpp)
SRCS+= $(shell ls settings/*.cpp)
SRCS+= $(shell ls misc/*.cpp)
SRCS+= $(shell ls io/*.cpp)
SRCS+= $(shell ls evolution/*.cpp)
SRCS+= $(shell ls evolution/crossoverFunctions/*.cpp)
SRCS+= $(shell ls evolution/mutationFunctions/*.cpp)
SRCS+= $(shell ls evolution/fitnessFunctions/*.cpp)
SRCS+= $(shell ls evolution/constraints/*.cpp)
SRCS+= $(shell ls evolution/penalty/*.cpp)
SRCS+= $(shell ls geometry/*.cpp)
SRCS+= $(shell ls geometry/shapes/*.cpp)
SRCS+= $(shell ls dataStructures/*.cpp)
#SRCS+= $(shell ls dataStructures/*.cpp)
SRCS+= $(shell ls test/*.cpp)

OBJS= $(patsubst %.cpp, %.o, $(SRCS))

all: $(PROD)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $< -o $@ #$(LIBGL) #$(LIBGLUT) $(LIBGL) $(LIBS)

$(PROD): $(OBJS)
	$(CC) -o $(PROD) $^ $(LIBS)

clean:
	rm -f $(PROD)
	rm -f *.o
	rm -f ui/*.o
	rm -f settings/*.o
	rm -f misc/*.o
	rm -f io/*.o
	rm -f evolution/*.o
	rm -f evolution/crossoverFunctions/*.o
	rm -f evolution/mutationFunctions/*.o
	rm -f evolution/fitnessFunctions/*.o
	rm -f evolution/constraints/*.o
	rm -f evolution/penalty/*.o
	rm -f geometry/*.o
	rm -f geometry/shapes/*.o
	rm -f dataStructures/*.o
	rm -f test/*.o
