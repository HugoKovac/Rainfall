void greetuser(char param_1)
{
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  undefined2 local_3c;
  char local_3a;
  
  if (language == 1) {
    local_4c = 0xc3767948;
    local_48 = 0x20a4c3a4;
    local_44 = 0x69a4c370;
    local_40 = 0xc3a4c376;
    local_3c = 0x20a4;
    local_3a = 0;
  }
  else if (language == 2) {
    local_4c = 0x64656f47;
    local_48 = 0x64696d65;
    local_44 = 0x21676164;
    local_40 = CONCAT22(local_40._2_2_,0x20);
  }
  else if (language == 0) {
    local_4c = 0x6c6c6548;
    local_48 = CONCAT13(local_48._3_1_,0x206f);
  }
  strcat((char *)&local_4c,&param_1);
  puts((char *)&local_4c);
  return;
}

int main(int param_1,int param_2)
{
  int uVar1;
  char *__s1;
  int iVar2;
  int *puVar3;
  int *puVar4;
  byte bVar5;
  char *pcVar6;
  int local_60 [10];
  char acStack_38 [36];
  char *local_14;
  
  bVar5 = 0;
  if (param_1 == 3) {
    puVar3 = local_60;
    for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    strncpy((char *)local_60,*(char **)(param_2 + 4),0x28);
    pcVar6 = "LANG";
    __s1 = getenv("LANG");
    local_14 = __s1;
    if (__s1 != (char *)0x0) {
      iVar2 = memcmp(__s1,&DAT_0804873d,2);
      if (iVar2 == 0) {
        language = 1;
        pcVar6 = __s1;
      }
      else {
        pcVar6 = local_14;
        iVar2 = memcmp(local_14,&DAT_08048740,2);
        if (iVar2 == 0) {
          language = 2;
        }
      }
    }
    puVar3 = local_60;
    puVar4 = (int *)&stack0xffffff50;
    for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    uVar1 = greetuser((char)pcVar6);
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}