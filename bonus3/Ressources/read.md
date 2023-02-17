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