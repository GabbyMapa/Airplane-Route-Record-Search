myProgram: main.o records.o
	gcc main.o records.o -o myProgram
main.o: records.h main.c
	gcc -c main.c
records.o: records.h records.c
	gcc -c records.c 
clean:
	rm *.o myProgram
