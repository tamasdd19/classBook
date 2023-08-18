LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3 -lcrypto

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

EXECUTABLE = classBook.exe

.PHONY: clean all run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	g++ -o $@ $^ -Iinclude/ -Linclude/lib $(LIBS)

%.o: %.cpp
	g++ -c -o $@ $< -Iinclude/

clean:
	del $(EXECUTABLE)

run: all
	./$(EXECUTABLE)
