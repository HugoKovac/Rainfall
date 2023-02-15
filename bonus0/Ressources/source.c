void p(char *param_1,char *param_2)
{
	/*
		param_1 and param_2 -> local var of pp
		local_100c -> local var if p

		read 4096 char from stdin to local_100c (size of 4104)
		strchr looking \n in local_100c, if found replace by \0
		copy 20 first char of local_100c in param_1 (local_34 of local_20 of main)
	*/
  char *pcVar1;
  char local_100c [4104];
  
  puts(param_2);
  read(0,local_100c,0x1000);
  pcVar1 = strchr(local_100c,10);
  *pcVar1 = '\0';
  strncpy(param_1,local_100c,0x14);
  return;
}

void pp(char *param_1)
{
	/*
		param_1 -> local var of main

		call p with local_34
		call p with local_20

		cpy local_34 (size 20) in param_1 (size 54)
		uVar2 = 0xffffffff;
		(char *)pcVar3 = param_1
		bVar4 = 0

		do {
			si uVar2 == 0, break

			uVar2 -= 1

			cVar1 = *pcVar3 (*param_1)

			pcVar3++
		}
		While cVar1(*param_1) != '\0'

		(uVar2 = 0xffffffff - len of param_1)
		param_1 + ((inverted bit of uVar2) - 1) = 32
		(with 20 -> param_1 + 20 - 1 = 32 )
	*/
  char cVar1;
  uint uVar2;
  char *pcVar3;
  byte bVar4;
  char local_34 [20];
  char local_20 [20];
  
  bVar4 = 0;
  p(local_34," - ");
  p(local_20," - ");
  strcpy(param_1,local_34);
  uVar2 = 0xffffffff;
  pcVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + (uint)bVar4 * -2 + 1;
  } while (cVar1 != '\0');
  *(undefined2 *)(param_1 + (~uVar2 - 1)) = 0x20;
  strcat(param_1,local_20);
  return;
}

11111111111111111111111111101011
00000000000000000000000000010100

undefined4 main(void)
{
  char local_3a [54];
  
  pp(local_3a);
  puts(local_3a);
  return 0;
}