#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NOTE_SZ 0x50
#define NOTE_CNT 0x10

char *array[NOTE_CNT];

int read_int() {
	char nptr[16];
	nptr[read(0, nptr, sizeof(nptr)-1)] = '\0';
	return atoi(nptr);
}

void add(){
	/* find an empty slot */
	int i;
	for (i = 0; i < NOTE_CNT; i++) {
		if (!array[i]) {
			break;
		}
	}

	if (i == NOTE_CNT) {
		puts("out of slots!");
		exit(-1);
	}

	/* create note */
	char *ptr = (char *)malloc(NOTE_SZ);

	if (!ptr) {
		puts("no memory!");
		exit(-1);
	}

	puts("content: ");
	read(0, ptr, NOTE_SZ);
	array[i] = ptr;

	puts("done");
}

void delete(){

	int idx;
	puts("index: ");
	idx = read_int();
	
	if (idx < 0 || idx >= NOTE_CNT || !array[idx]) {
		puts("invalid index");
		exit(-1);
	}

	free(array[idx]);	
	puts("done");
}

void view(){

	int idx;
	puts("index: ");
	idx = read_int();
	
	if (idx < 0 || idx >= NOTE_CNT || !array[idx]) {
		puts("invalid index");
		exit(-1);
	}

	printf("content: %s\n",array[idx]);	
}

void printmenu(){
	puts("Now you can pull of some complex tcache exploits");
	puts("[1] Add note\n[2] Delete note\n[3] View note");
}



int main(int argc, char **argv){
	
	int choice;

	while(1) {
		printmenu();
		puts("choice: ");
		choice = read_int();
		if (choice == 1) {
			add();
		}
		else if (choice == 2) {
			delete();
		}
		else if (choice == 3) {
			view();
		}
		else {
			puts("invalid choice");
			return -1;
		}
	}

	return 0;
}