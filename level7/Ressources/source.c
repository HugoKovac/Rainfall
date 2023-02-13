void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	time_t param2;

	param2 = time((time_t *)0x0);
	printf("%s - %d\n", c, param2);
	return;
}

/*
	param_2 = av
	puVar1 size of 8
	puVar1 = 1
	puVar2 size of 8
	puVar1[1] = puVar2
	puVar3 size of 8
	puVar3 = 2
	puVar2 size of 8, previous malloced address in puVar1[1]
	puVar3[1] = puVar2, newly allocated address
	copy 1st srgument in puVar1[1], puVar1 as string, so puVar1[1] as char
	copy 2nd srgument in puVar3[1], puVar3 as string, so puVar3[1] as char
	open "/home/user/level8/.pass" in FILE *__stream
	set value of __stream in the global var c for the size of 0x44
	print "~~"
*/
undefined4 main(undefined4 param_1, int param_2)
{
	undefined4 *puVar1;
	void *pvVar2;
	undefined4 *puVar3;
	FILE *__stream;

	puVar1 = (undefined4 *)malloc(8);
	*puVar1 = 1;
	pvVar2 = malloc(8);
	puVar1[1] = pvVar2;
	puVar3 = (undefined4 *)malloc(8);
	*puVar3 = 2;	pvVar2 = malloc(8);
	puVar3[1] = pvVar2;
	strcpy((char *)puVar1[1], *(char **)(param_2 + 4));
	strcpy((char *)puVar3[1], *(char **)(param_2 + 8));
	__stream = fopen("/home/user/level8/.pass", "r");
	fgets(c, 0x44, __stream);
	puts("~~");
	return 0;
}