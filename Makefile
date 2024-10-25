programa: fila.o lista.o pilha.o main.o 
    gcc -o programa fila.o lista.o pilha.o main.o

main.o: main.c fila.h lista.h pilha.h erro.h
    gcc -c main.c

fila.o: fila.c fila.h
    gcc -c fila.c

lista.o: lista.c lista.h
    gcc -c lista.c

pilha.o: pilha.c pilha.h
    gcc -c pilha.c

clean:
    rm *.o programa