# The PATH enviroment variable

Enviroment variables store information about the current environment. I've already shown you ways to affect the visibility of environment variables and the effects they have on your environment through the use of `export`. 

One of the well-known and frequently modified variables is the PATH variable. In general this changes which executable programs are accessible by your current environment.

You can 

```
$echo $PATH
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
```

These are the locations of the executables that are easily visible in your current environment. Notice that the path is separated by colons. That's just the way it's formatted. What are some executables you have been using in this class?

1. md5sum
2. cat
3. ls
4. mv
5. cp
6. vim
7. accept other class contributions.

Type `which` and the program name for any one of these and you'll see that it is in one of the PATH directories.

e.g.
```
$which vim
/usr/bin/vim
```

You could also type `/usr/bin/vim` and it would work, but since it's in your PATH you don't need to specify the full path to vim. You can try that with other programs we're using too! e.g. `which cat`, then type the full path it gives you and you'll see it runs the same. 

You can make a custom executable program, e.g.

```
#!/bin/bash
echo "hello world"
```
save as program, chmod to 777, and then type "program" - it won't run! but you can type /path/to/you/program and it will run. It doesn't run by you just providing the name because it isn't in your PATH.

## Changing your PATH
You might want to change your path at times to make programs you write  visible. To drill the concept home of PATH visibility, copy your program to a location in your path.

```
$mv hello /usr/local/games
$hello
hello world
```

but now let's change our path so that the program is visible without having to move it to somewhere in your path.

```
# move hello program to /opt
# add export PATH=/opt:$PATH to the .bashrc file
$which hello
/opt/hello
```

So that's how you change your PATH, and that's what the PATH is all about. The are other syntaxes for changing the PATH and other means to do it, but this will suffice for us for now.

# Binary vs. Executable ( A Vocabulary Lesson )
The expressions "binary" and "executable" are used interchangeably in Linux circles, but they don't always mean the same thing. And ".exe" in windows in an executable file. A file with x permission is executable. When people refer to a binary/executable they generally mean a file that is compiled into a binary format that the machine can read and run. Like "cat" is a binary file. If you 

```
vim /bin/cat
```

you'll see its a  mess, it's a binary file that's compiled to be read b y a computer, it's not a text file that a human can read. Thats why when you look at it with vim you see unreadable junk.
