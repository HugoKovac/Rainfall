```log
0x08048ed4 <+20>:    call   0x8049710 <atoi>
0x08048ed9 <+25>:    cmp    eax,0x1a7
0x08048ede <+30>:    jne    0x8048f58 <main+152>
```
> Compare atoi(av[1]) with 423(0x1a7)

```sh
level0@RainFall:~$ ./level0 423
$
```
> We got a prompt (/bin/dash is executed)

```sh
$ id
uid=2030(level1) gid=2020(level0) groups=2030(level1),100(users),2020(level0)
```
> Our uid has change and we are in the group level1

```sh
cd /home/user/level1
```
> We go to the home directory of level1

```
cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
> We got the pass