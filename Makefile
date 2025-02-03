# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pthread

# Source files
SOURCES = fork-join.c rendezvous.c barrier.c reader-writer.c reader-writer-nostarve.c mutex-nostarve.c

# Executables
EXECUTABLES = fork-join rendezvous barrier reader-writer reader-writer-nostarve mutex-nostarve

# Default target: Compile all programs
all: $(EXECUTABLES)

# Rule to compile each .c file into an executable
fork-join: fork-join.c
	$(CC) $(CFLAGS) -o fork-join fork-join.c

rendezvous: rendezvous.c
	$(CC) $(CFLAGS) -o rendezvous rendezvous.c

barrier: barrier.c
	$(CC) $(CFLAGS) -o barrier barrier.c

reader-writer: reader-writer.c
	$(CC) $(CFLAGS) -o reader-writer reader-writer.c

reader-writer-nostarve: reader-writer-nostarve.c
	$(CC) $(CFLAGS) -o reader-writer-nostarve reader-writer-nostarve.c

mutex-nostarve: mutex-nostarve.c
	$(CC) $(CFLAGS) -o mutex-nostarve mutex-nostarve.c

dining-philosophers: dining-philosophers.c
	$(CC) $(CFLAGS) -o dining-philosophers dining-philosophers.c

# Clean up compiled files
clean:
	rm -f $(EXECUTABLES)