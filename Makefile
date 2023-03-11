# Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=tema1

build: $(TARGETS)

tema1: main.c auxiliary.c functions.c
	$(CC) $(CFLAGS) main.c auxiliary.c functions.c -o tema1	

clean:
	rm -f $(TARGETS)
