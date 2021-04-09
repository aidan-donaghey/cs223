CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: decrypt

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
decrypt:  decrypt.o dict.o 
	$(CC) $(CFLAGS) -o decrypt decrypt.o dict.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
decrypt.o:  decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
dict.o:  dict.c dict.h
	$(CC) $(CFLAGS) -c dict.c


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) decrypt *.o *~