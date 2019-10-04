CXX = gcc
EXEC = test

CXXFLAGS = -Wall -W -pedantic -D uint_8="unsigned char" -D uint_32="unsigned int"
LDFLAGS =


SRC = PC_decode_test.c ../frames_definition.c ../frames_get.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf *.o
	rm -f $(EXEC)
