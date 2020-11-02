CC= gcc -Wall -pedantic -O2
LIBS= -lm
HEADER_FILES_DIR = ./
INCLUDES = -I $(HEADER_FILES_DIR)
MAIN= tsp.out
SRCS = main.c grafo.c TSP.c lista.tabu.c
DEPS = grafo.h TPS.h lista.tabu.h
OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~
