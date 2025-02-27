EXEC=prog
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

%.o: %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
	
# make all pour la compilation et ./prog pour l'exécution du programme
# make clean pour la suppression de tous les fichiers objets
# make mrproper pour la suppresion de tous les fichiers objets et de l'exécutable
	
