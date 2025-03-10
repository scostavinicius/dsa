PROJETO = bin/programa

SRC = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

all: $(PROJETO)

$(PROJETO): $(OBJS)
	g++ -Wall -Iinclude $^ -o $@

build/%.o: src/%.cpp
	g++ -Iinclude -c $< -o $@

clean:
	del build\*.o bin\programa.exe

run:
	./bin/programa