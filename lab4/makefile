CC=gcc
CFLAGS=-g

all: hell hard easy baby

hell: hell.c
	$(CC) $(CFLAGS) -fPIE -Wl,-z,relro,-z,now -o hell hell.c

hard: easy.c
	$(CC) $(CFLAGS) -fPIE -Wl,-z,relro,-z,now -o hard easy.c

easy: easy.c
	$(CC) $(CFLAGS) -no-pie -o easy easy.c

baby: baby.c
	$(CC) $(CFLAGS) -no-pie -o baby baby.c

clean:
	rm -f hell hard easy baby
