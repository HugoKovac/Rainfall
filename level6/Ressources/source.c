
void n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return;
}

void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	puts("Nope");
	return;
}

/*
	param_2 is the pointer char** av
	__dest is a string of size 64
	ppcVar1 alloc size for 4 pointers
	ppcVar1[0] = m
	set the 1rd arguement in __dest (param_2 + 4 == av + 1, the offset of char ** and int are not the same)
	ppcVar1[0], so m is run
*/

void main(undefined4 param_1, int param_2)
{
	char *__dest;
	code **ppcVar1;

	__dest = (char *)malloc(0x40);
	ppcVar1 = (code **)malloc(4);
	*ppcVar1 = m;//value is 
	strcpy(__dest, *(char **)(param_2 + 4));
	(**ppcVar1)();
	return;
}