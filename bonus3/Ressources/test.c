#include <string.h>
#include <stdio.h>

int main(){
	char local_98[50] = "test";
	int iVar2 = atoi("0");
	printf("%d\n", iVar2);
	*(char *)((int)local_98 + iVar2) = 0;
	int test = strcmp(local_98, 0);
	printf("%d\n", test);
}