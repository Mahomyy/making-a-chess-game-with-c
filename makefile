all: main.c GUI.c Game.c
	gcc main.c GUI.c Game.c -o main -I/opt/homebrew/opt/sdl2/include/ -L/opt/homebrew/opt/sdl2/lib -lSDL2

main.o: main.c GUI.h Game.h
	gcc main.c -c -o main.o -I/opt/homebrew/opt/sdl2/include/ -L/opt/homebrew/opt/sdl2/lib -lSDL2

GUI.o: GUI.c GUI.h
	gcc GUI.c -c -o GUI.o -I/opt/homebrew/opt/sdl2/include/ -L/opt/homebrew/opt/sdl2/lib -lSDL2

Game.o: Game.c Game.h
	gcc Game.c -c -o Game.o -I/opt/homebrew/opt/sdl2/include/ -L/opt/homebrew/opt/sdl2/lib -lSDL2
