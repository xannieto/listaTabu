CC= gcc -Wall -pedantic
HEADER_FILES_DIR = ./
INCLUDES = -I $(HEADER_FILES_DIR)
MAIN= analizador.out
SRCS = main.c abb.c analizador.lexico.c analizador.sintactico.c definicions.c erros.c sistema.es.c taboa.simbolos.c
DEPS = abb.h analizador.lexico.h analizador.sintactico.h definicions.h erros.h sistema.es.h taboa.simbolos.h
OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~
