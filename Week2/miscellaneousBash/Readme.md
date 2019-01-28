# Some more bash syntax


## xargs
Needed for homework!
Accepts a pipe and performs the indicated operation on all the lines given via standard in.

E.g. 
```
$ cat FILENAME
a
b
c
$ cat FILENAME | xargs touch
$ ls
a b c
$ cat FILENAME | xargs rm
```
So, for example, if you have a list of pids...
```
$ cat pids.txt
8903
7891
$ cat pids.txt | xargs kill -SIGTERM
```
will [try to] stop them by issuing a SIGTERM to each one.


##bash functions
https://www.linuxjournal.com/content/return-values-bash-functions
If you feel like writing functions, go ahead.
see functions.sh


## cowsay
cowsay something

## tee
```
$ls -l / | tee rootDirectory.txt 
```
[youll see shell output.]
```
$cat rootDirectory.txt
```

## tree
$apt-get install tree
$mkdir -p a/{b,c}/{d,e,f}
$tree a

## eval
Evaluate a string as if it is code.
eval "ls -l"
