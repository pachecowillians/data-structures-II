all: ARN

ARN: main.o ARN.o
	gcc -o ARN main.o ARN.o

main.o: main.c ARN.h
	gcc -c main.c -Wall

ARN.o: ARN.c ARN.h
	gcc -c ARN.c -Wall

clean:
	rm ARN main.o ARN.o
