CC= g++

LIBS =
OBJ = src/graphviewer.O, src/connection.o, src/FileReader.o, src/Location.o, src/Main.O

CFLAGS = -g -Wall -Wextra -MMD

all: proj

%.o %.cpp
				$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

proj: $(OBJ)
				$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
		rm -rf src/*.d
		rm -rf src/*.o
		rm -rf proj