all:   	
	@gcc -std=c99 -c livro.c
	@gcc -std=c99 -c main.c
	@gcc main.o livro.o -o programa

run:
	@./programa 
