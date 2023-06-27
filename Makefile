LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

EXECUTABLE = main.exe

.PHONY: clean all run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	g++ -o $@ $^ -Iinclude/ -Linclude/lib $(LIBS)

%.o: %.cpp
	g++ -c -o $@ $< -Iinclude/

clean:
	rm -f $(OBJS) $(EXECUTABLE)

run: all
	./$(EXECUTABLE)
