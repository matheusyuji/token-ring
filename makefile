PROG = game
OBJS = main.o

CFLAGS = -g
CC = gcc

all: $(PROG)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

clean: 
	@rm -f $(OBJS)

purge: clean
	@rm -f $(PROG) core a.out