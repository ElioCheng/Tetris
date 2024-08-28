CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD -Werror=vla
EXEC = biquadris
OBJECTS = window.o Block.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o StarBlock.o TBlock.o ZBlock.o Pixel.o Level.o Level0.o Level1.o Level2.o Level3.o Level4.o Level5.o Gameboard.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
SRC = ${OBJECTS:.o=.cc}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${SRC} -o ${EXEC} -lX11 

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

