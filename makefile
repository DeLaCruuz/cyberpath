CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

SRCS = main.c header.c
OBJS = $(SRCS:.c=.o)
EXEC = jeu

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(EXEC)