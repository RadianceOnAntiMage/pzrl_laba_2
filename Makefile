all: prog
.PHONY: test clean

prog: main.o lab.o
	gcc -o prog main.o lab.o

main.o: main.c
	gcc -c main.c

lab.o: lab.c
	gcc -c lab.c

test: prog
	./prog input.txt -r "Sharik" "Bobik"
	

clean:
	rm -f prog *.o output.txt
