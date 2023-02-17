int main(int param_1, int param_2)

{
	int uVar1;
	int iVar2;
	int *puVar3;
	byte bVar4;
	int local_98[16];
	char local_57;
	char local_56[66];
	FILE *local_14;

	bVar4 = 0;
	local_14 = fopen("/home/user/end/.pass", "r");
	puVar3 = local_98;
	for (iVar2 = 0x21; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
	}															   // set local_98(size 16) string to '\0' on 0x21 bytes (33-16 = overflow of 17)
	if ((local_14 == (FILE *)0x0) || (param_1 != 2))
	{ // file don't exit or no rights or ac != 2
		uVar1 = 0xffffffff;
	}
	else
	{
		fread(local_98, 1, 0x42, local_14);						   // set 0x42 of &.pass in local_98 (66-16 = overflow of 50)
		local_57 = 0;
		iVar2 = atoi(*(char **)(param_2 + 4));
		*(char *)((int)local_98 + iVar2) = 0;				   // set null byte to local_98 at he given av[1]
		fread(local_56, 1, 0x41, local_14);						   // set 0x41 of &.pass[0x42] in local_56 (65-16 = overflow of 49)
		fclose(local_14);										   // close .pass
		iVar2 = strcmp((char *)local_98, *(char **)(param_2 + 4)); // if av[1] == local_98 exec /bin/sh
		if (iVar2 == 0)
		{
			execl("/bin/sh", "sh", 0);
		}
		else
		{
			puts(local_56);
		}
		uVar1 = 0;
	}
	return uVar1;
}