CC=gcc
CFLAGS=-no-pie -g -fno-stack-protector

attackme: main.c
	$(CC) $(CFLAGS) -o attackme main.c

clean:
	rm -f attackme
