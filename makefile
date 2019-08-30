CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = menu.o animal.o tiger.o turtle.o penguin.o zoo.o userDefined.o

SRCS = menu.cpp animal.cpp tiger.cpp turtle.cpp penguin.cpp zoo.cpp userDefined.cpp

HEADERS = menu.hpp animal.hpp tiger.hpp turtle.hpp penguin.hpp zoo.hpp userDefined.hpp

all: prog

prog: ${OBJS} main.o
	${CXX} ${CXXFLAGS} ${OBJS} main.o -o prog

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o prog
