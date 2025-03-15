CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/tokenizer.c src/symboltable.c src/hash_table.c src/a_to_m.c src/opcodes_entry.c
OBJ = $(SRC:.c=.o)
EXEC = atom

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
	rm -f output.txt
