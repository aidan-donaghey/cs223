CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: pfml

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
pfml:  pfml.o FileManagement.o
	$(CC) $(CFLAGS) -o pfml pfml.o FileManagement.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
pfml.o:  pfml.c 
	$(CC) $(CFLAGS) -c pfml.c FileManagement.h



# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
FileManagement.o: FileManagement.c 
	$(CC) $(CFLAGS) -c FileManagement.c FileManagement.h


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) compress *.o *~