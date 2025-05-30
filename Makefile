all: result.exe

result.exe: main.o result.c
	gcc main.o result.c -o result.exe

main.o: main.c main.h
	gcc -c main.c -o main.o

clean:
	rm -f *.o *.exe