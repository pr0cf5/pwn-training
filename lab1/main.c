#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef void (*funcptr) (void);

void vuln(){
	char buf[0x10];
	printf("give me your name: \n");
	gets(buf);
}

void setup_stack(funcptr fp){
	void *stack_ptr = (void *)0xdead000;
	if (stack_ptr != mmap(stack_ptr, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANONYMOUS|MAP_FIXED|MAP_PRIVATE|MAP_GROWSDOWN, -1, 0)) {
		perror("mmap");
		exit(-1);
	}
	asm volatile ("mov $0xdead000, %rsp");
	fp();
}

int main(int argc, char **argv){
	setup_stack(vuln);
	return 0;
}