# Nome do executável
EXEC = sistema_leilao.exe

CC = gcc

CFLAGS = -Wall -g

OBJ = main.o fila.o lista.o pilha.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilar main
main.o: main.c fila.h lista.h pilha.h erro.h
	$(CC) $(CFLAGS) -c main.c

# Compilar fila
fila.o: fila.c fila.h erro.h
	$(CC) $(CFLAGS) -c fila.c

# Compilar lista
lista.o: lista.c lista.h erro.h
	$(CC) $(CFLAGS) -c lista.c

# Compilar pilha
pilha.o: pilha.c pilha.h erro.h
	$(CC) $(CFLAGS) -c pilha.c

# Limpeza de arquivos .o e .exe
clean:
	rm -f $(OBJ) $(EXEC)
