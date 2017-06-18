TARGET = puzzle
SRC = main.c
CFLAGS = -g -Wall -O2 -pedantic-errors -std=gnu99
CX = gcc
HEADER =

default: $(SRC)
	$(CX) $(SRC) $(HEADER) $(CFLAGS) -o $(TARGET)

debug: $(SRC)
	$(CX) $(SRC) $(HEADER) $(CFLAGS) -o $(TARGET) -DEBUG

clean:
	rm -f $(TARGET) *.o
