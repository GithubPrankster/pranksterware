CC = gcc
CCX = -s -O3 -m64 -static-libgcc
LIBS = -lSDL2main -lSDL2
WIN_LIBS = -lmingw32 -mwindows -mconsole $(LIBS) 

windows:
	$(CC) $(CCX) snake.c $(WIN_LIBS) -o snake.exe

unix:
	$(CC) $(CCX) snake.c $(LIBS) -o snake