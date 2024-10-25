CC = gcc
CFLAGS = -Wall -g
OBJ = fila.o lista.o pilha.o main.o
DEPS = fila.h lista.h pilha.h erro.h

programa: $(OBJ)
	$(CC) -o $@ $(OBJ)

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c main.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c

pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

clean:
	rm -f *.o programa
