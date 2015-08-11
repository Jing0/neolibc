PROGS   = test
OBJS    = neostring.o
FLAGS   = -Wall 
CC      = gcc

ALL: $(OBJS) $(PROGS)

%.o: %.c %.h
	$(CC) -c $^ $(FLAGS)

test: test.o $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	$(RM) $(OBJS) $(PROGS) $(wildcard *.h.gch) $(wildcard *.o)
