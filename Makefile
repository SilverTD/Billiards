CC = g++

INCLUDE = -I ./include

CFLAGSO = -std=c++17 -Wall ${INCLUDE}

LIBS = -lSDL2main -lSDL2 -lSDL2_image

CFLAGSB = ${LIBS}

build:
	${CC} ./src/*.cpp ${CFLAGSO} ${CFLAGSB} -o main
