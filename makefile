## Makefile
## Author: Batuhan Sazak und Mehraj Singh Randhawa
## Last Modified: 25.04.2020
##
## Version: 1.0
##
##


## ------variables------

CC = gcc
CFLAGS=-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11
OBJECTS= main.c mypopen.c
## ------rules------
##

%.o: %.c
	$(CC) $(CFLAGS) -c $<

##
## ------targets------
##
## $(CFLAGS) -o testpipe

all:

	echo build, clean 

build: 
	clear
	$(CC) $(OBJECTS) $(CFLAGS) -o mypopen.o
	
clean:
	clear
	$(RM) *.o *~ mypopen.o
	
	
full:
	clear
	$(RM) *.o *~ mypopen.o
	$(CC) $(OBJECTS) -o mypopen.o
	./mypopen.o


