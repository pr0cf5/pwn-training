#include <stdio.h>
#include <stdlib.h>

void vuln(){
	char buf[0x50];
	printf("give me your name: \n");
	gets(buf);
}


int main(int argc, char **argv){
	vuln();
	return 0;
}