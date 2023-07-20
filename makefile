main: main.o records.o
	gcc main.o records.o -o main
main.o: main.c records.h
	gcc -c main.c 
records.o: records.c records.h
	gcc -c records.c 
clean:
	rm main
	rm main.o
	rm records.o
run:
	./main data.csv