CC = gcc
CFLAGS = -g -Wall -pedantic-errors -std=gnu99
TARGET = puzzle
SRCS = control.c search.c auto_solve.c
HEADERS = control.h search.h auto_solve.h
TESTS = test_search.c test_control.c test_auto.c



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
	$(CC) $(SRCS) test_auto.c $(CFLAGS) -o test_auto

debugtest: $(TESTS) $(SRCS) $(HEADERS)
	$(CC) $(SRCS) test_search.c $(CFLAGS) -o test_search -DEBUG
	$(CC) $(SRCS) test_control.c $(CFLAGS) -o test_control -DEBUG
	$(CC) $(SRCS) test_auto.c $(CFLAGS) -o test_auto -DEBUG


.PHONY: clean
clean:
	rm -f $(TARGET) *.o test_search test_control test_auto out *.out
