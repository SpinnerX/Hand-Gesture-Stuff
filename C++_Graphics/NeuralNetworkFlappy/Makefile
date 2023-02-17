CC = g++
CCFLAGS = -std=c++2a -g -fsanitize=address

HH = $(shell find . -name '*.h')
CPP = $(shell find . -name '*.cc')

TESTS = $(shell find . -name *.cpp)

LIBS = `pkg-config --cflags --libs sfml-graphics`

a.out: $(HH)
	$(CC) $(CCFLAGS) $(CPP) $(LIBS)

clean:
	rm -rf a.out *.o core a.out.dSYM

