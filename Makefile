all:clean compile

compile:
	gcc backtrack.c -o backtrack.out
	gcc dynamic.c -o dynamic.out 
	gcc bruteForce.c -o bruteForce.out -lm
	gcc huffman.c -o huffman.out

clean:
	rm -rf *.out
