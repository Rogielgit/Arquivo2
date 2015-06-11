all:   	
	@gcc -std=c99 -c livro.c
	@gcc -std=c99 -c Lista.c
	@gcc -std=c99 -c main.c
	@gcc main.o livro.o Lista.o -o programa

run:
	@./programa 
