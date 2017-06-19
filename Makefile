CC = gcc
CFLAGS = -g -Wall -O2 -pedantic-errors -std=gnu99
TARGET = puzzle
SRCS = control.c search.c auto_solve.c
HEADERS = control.h search.h auto_solve.h
TESTS = test_search.c test_control.c



all: puzzle test

run: puzzle
	./puzzle > out

puzzle: main.c main.h $(SRCS) $(HEADERS)
	$(CC) $(SRCS) main.c $(CFLAGS) -o $(TARGET)

debug: main.c main.h $(SRCS) $(HEADERS)
	$(CC) $(SRCS) main.c $(CFLAGS) -o $(TARGET) -DEBUG

test: $(TESTS) $(SRCS) $(HEADERS)
	$(CC) $(SRCS) test_search.c $(CFLAGS) -o test_search
	$(CC) $(SRCS) test_control.c $(CFLAGS) -o test_control

debugtest: $(TESTS) $(SRCS) $(HEADERS)
	$(CC) $(SRCS) test_search.c $(CFLAGS) -o test_search -DEBUG
	$(CC) $(SRCS) test_control.c $(CFLAGS) -o test_control -DEBUG


.PHONY: clean
clean:
	rm -f $(TARGET) *.o test_search test_control
