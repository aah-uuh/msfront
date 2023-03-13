CC := g++
CXXFLAGS := -O2 -g -Wall -Wextra -Wpedantic -Wno-unused-parameter -Iinclude
SRCS := $(wildcard *.cpp)

all: msfront

msfront:
	${CC} ${CXXFLAGS} -o $@ ${SRCS}


clean:
	-rm -f msfront