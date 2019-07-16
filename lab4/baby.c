#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NOTE_CNT 0x10

char *array[NOTE_CNT];
char global_buffer[0x100];

struct MEM {
	void *read_ptr;
	void *write_ptr;
	size_t limit;
};

struct MEM *myobj;

int read_int() {
	char nptr[16];
	nptr[read(0, nptr, sizeof(nptr)-1)] = '\0';
	return atoi(nptr);
}

void add(){
	/* find an empty slot */
	int i, sz;
	char *ptr;

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
	puts("size: ");
	sz = read_int();
	ptr = (char *)malloc(sz);

	if (!ptr) {
		puts("no memory!");
		exit(-1);
	}

	puts("content: ");
	read(0, ptr, sz);
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

void allocate_memobj() {
	myobj = (struct MEM *)malloc(sizeof(struct MEM));

	if (!myobj) {
		puts("no memory!");
		exit(-1);
	}

	myobj->read_ptr = global_buffer;
	myobj->write_ptr = global_buffer;
	myobj->limit = sizeof(global_buffer);
}

void free_memobj() {

	if (myobj) {
		free(myobj);
	}

}

void use_memobj() {
	if (!myobj) {
		puts("object not present");
		return;
	}

	write(1, myobj->write_ptr, myobj->limit);
	read(0, myobj->read_ptr, myobj->limit);
	puts("done");
}

void printmenu(){
	puts("A very baby-ish tcache challenge!");
	puts("[1] Add note\n[2] Delete note\n[3] View note\n[4] Allocate object\n[5] Delete Object\n[6] Use object");
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
		else if (choice == 4) {
			allocate_memobj();
		}
		else if (choice == 5) {
			free_memobj();
		}
		else if (choice == 6) {
			use_memobj();
		}
		else {
			puts("invalid choice");
			return -1;
		}
	}

	return 0;
}