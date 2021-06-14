all: Huffman

Huffman: main.o Huffman.o
	gcc -o Huffman main.o Huffman.o

main.o: main.c Huffman.h
	gcc -c main.c -Wall

Huffman.o: Huffman.c Huffman.h
	gcc -c Huffman.c -Wall

clean:
	rm Huffman main.o Huffman.o
