all:   	
	@gcc -std=c99 -c Lista.c
	@gcc -std=c99 -c Indice.c   	
	@gcc -std=c99 -c livro.c
	@gcc -std=c99 -c main.c
	@gcc main.o Lista.o livro.o Indice.o -o programa

run:
	@./programa 
