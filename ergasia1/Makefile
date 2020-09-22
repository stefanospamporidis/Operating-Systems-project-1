OBJS = Componentsqueue.o askisi1.o
SOURCE = Componentsqueue.c askisi1.c
HEADER = Componentsqueue.h askisi1.h
OUT = ergasia1
CC = gcc
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

askisi1.o: askisi1.c
	$(CC) $(FLAGS) askisi1.c

Componentsqueue.o: Componentsqueue.c
	$(CC) $(FLAGS) Componentsqueue.c

clean:
	rn -f $(OBJS) $(OUT)
