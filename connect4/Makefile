CC = gcc
CCX = -s -O3 -m64 -static-libgcc
LIBS = -lSDL2main -lSDL2
WIN_LIBS = -lmingw32 -mwindows -mconsole $(LIBS) 
NAME = connect4

windows:
	$(CC) $(CCX) $(NAME).c $(WIN_LIBS) -o $(NAME).exe

unix:
	$(CC) $(CCX) $(NAME).c $(LIBS) -o $(NAME)