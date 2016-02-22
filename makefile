CXX=clang++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field
BINARIES = prog2
all: ${BINARIES}
prog2: Main.o Encoder.o Node.o
	${CXX} $^ -o $@
clean:
	/bin/rm -f ${BINARIES} *.o


