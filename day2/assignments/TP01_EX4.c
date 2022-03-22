#include <stdio.h>
#include <stdlib.h>

int main(){
	int* p;
	p = (int*)malloc(sizeof(int)*4);
	p[0] = 2;
	p[1] = 1; 
	p[2] = 6;
	p[3] = 456;
	for(int i = 0; i < 4; i++){
		printf("%d\n", *(p+i));
	}
	free(p);
}
