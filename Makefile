LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

SRCS = $(wildcard src/*.cpp)

clean:
	del main.exe

all:
	g++ -o main.exe $(SRCS) -Iinclude/ -Linclude/lib  $(LIBS)

run: all
	main.exe
