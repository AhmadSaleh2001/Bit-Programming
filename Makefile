CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = bitmap.o main.o
EXE = main.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

bitmap.o: bitmap.c bitmap.h
	$(CC) $(CFLAGS) -c bitmap.c -o bitmap.o

main.o: main.c bitmap.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJ) $(EXE)