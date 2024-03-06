make:
	gcc main.c fonction.c -o prog -fopenmp
	./prog

clean:
	rm prog

debug:
	gcc -g main.c fonction.c -o prog -fopenmp
	gdb prog