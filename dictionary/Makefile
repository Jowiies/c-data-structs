# Compiler and flags

CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -std=c11 -I$(LIBDIR)

# Files
PROGRAM = program
LIBNAME = libdictionary.a
LIBDIR = libsrc
LIBHEAD = dictionary.h
LIBSRC = dictionary.c
LIBOBJ = dictionary.o 

all: $(PROGRAM)

# Compile the static library from source
$(LIBNAME): $(LIBDIR)/$(LIBOBJ)
	ar rcs $(LIBNAME) $(LIBDIR)/$(LIBOBJ)

# Compile lib.c -> lib.o
$(LIBOBJ): $(LIBDIR)/$(LIBSRC)
	$(CC) $(CFLAGS) -c $(LIBDIR)/$(LIBSRC) -o $(LIBDIR)/$(LIBOBJ)

# Compile main + lib link
$(PROGRAM): main.o $(LIBNAME)
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o -L. -ldictionary

# Compile main.c -> main.o
main.o: main.c $(LIBDIR)/$(LIBHEAD)
	$(CC) $(CFLAGS) -c main.c -o main.o

# Clean *.o && lib.a
clean:
	rm -f $(PROGRAM) main.o $(LIBDIR)/$(LIBOBJ) $(LIBNAME)