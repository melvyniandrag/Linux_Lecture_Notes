# More About BASH

## Introduction

So the purpose of last week was to give you a flavor of what Linux is all about and some basic bash commands. We never even got into what bash is!
Bash is a strange thing to describe. It's a language and also a unix shell, it's the language / tool you use to talk to your machine, run programs ,gather output, etc.. We learned a few commands like `cp` for copying files, `rm` for deleting files - and I forgot to tell you, to remove a directory you run `rm -r DIRECTORY` (example). There is also an `rmdir` command, but I never use it and have never seen anyone use it. `rmdir` expects the directory to be empty. `rm -r` removes all the files and the directory ( the -r means recursive )." The -r flag can be seen for other tools as well, like `cp`. Try to `cp` a directory, and you'll see it doesn't work. You have to use `cp -r` to copy the directory and its contents. We also learned about `mv`, `wget`, `file`, `unzip`, `tar`, `gunzip`, etc. 

We also learned a *bit* about vim, which is a powerful text editor. I wrote the entire mathtestmaker.com with vim, the python/django/latex/css/html/javascript, everything. It is very powerful and can be extended to do many things. Now today where going to go a bit deeper into linux, we'll learn a bit more about bash, about regular expressions, about linux processes, and we'll write a very useful script together.

For your assignment 1, I want to round out the topics you need to know to complete it. There are 5 "TODOS" in the assignment1_student.sh file in the Week1 directory in the class repository.
To complete this you need to know about 

## List of topics to cover

1. if
2. bash variables
3. md5sum
4. cut
5. return values in scripts
6. wc
7. pipes

### 1/7 if

The bash syntax for if is 
```
if [ condition ]
then
 command
fi
```

One more useful piece of information is that bash generally interprets values as strings, unless they can be used as numbers, in which case it assumes they are numbers. https://www.tldp.org/LDP/abs/html/untyped.html.

For example :

x1=1
x2=2
x3=11
x4=1a

Comparison operators for numbers in bash are:
-eq
-ne
-gt
-ge 
etc.

Comparison operators for strings are:
=
!=

for more information see here https://www.tldp.org/LDP/abs/html/comparison-ops.html

So in the above example:

if [ $x1 -lt $x2 ]
then
    echo "$x1 < $x2"
else
    echo "$x2 < $x1"
fi

see the myIf scripts

So I've shown you how to use if and some comparisons and highlighted some pitfalls, okay?

notice how I made variables and how I used them in here. Now I want to show you a bit more about variables in bash. Again, what I'm showing you will work with sh (probably) but I take no responsibility for it if it doesn't. There are a million shells out there - a cool one I came across recently is fish. I think you install it with apt-get install fish, or fsh, can't remember, but I guess it purports to be a beginner friendly shell. I've never had any issue with bash, I've used the c shell maybe once or twice on an old server, and zsh a few times, but I like bash.

Okay, so variables

7/7 bash variables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
you can either say 
variable=value
or
export variable=value

and you'll see them in scripts you download on the internet and tinker with. without export, the variable is only visible in your current shell. 
With export, its visible in your subshells. That's it!

try this in your shell:
x=1
echo $x
bash
echo $x
<Nothing!>
exit # exits the subshell
echo $x #there it is!

now try export y=1
echo $y
bash
echo $y
Something!

So depending on whether or not you need the variable in subshells / subprocesses, that determines whether or not you should export it. Why should you *not* export a variable. I can think of a few reasons why you wouldn't, though I haven't come across a situation like the one I'm dreaming up. So it's up to you and your use case whether you should export or not. 

2/7 md5sum
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
md5sum file. I told you what an md5sum is. to revisit it, md5sum computes a 128 bit hash of a file.
How many bits in a byte? (8) so how many bytes should we expect the hash to take up? 128/8 = 32. We'll revisit this in a minute.

returns $md5sum whitespace $filename

3/7 cut
**********************************
cut splits an input. There are many ways to split the input. I'll show you two now, one from last week, and another new way.
echo "hello world" | cut -d " " -f1
echo "hello world" | cut -c1-5

4/7 return values
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
The only thing to know for now is the one I showed you $?. The return value of the last command. You can use this to verify that a command exited successfully or not. If not, you can see the error code it exited with!

5/7 wc
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

wordcount

outputs newlines, words, bytes

echo "hello world"  | wc
1 2 12

Why 12 bytes? An ASCII character takes up one byte. Whats an ascii character? I'm actually an expert in text encodings because I worked for 2 years doing language analysis and computational linguistics and a big data start up. I can talk your ear off about that, but it's not relevant now .In any event, "hello world" has 11 characters, plus a newline character appended by echo.

To get rid of the newline, you can use an echo option that may or may not be available on your machine

echo -ne "hello" > log
wc log
0 1 5

6/7 pipes
************************************
We already reviewed pipes with the cut example:
echo "hello world" | cut -d" " -f1

Lets go back to the md5sum for a second though:
md5sum lecture.txt | cut -d " " -f1 | wc -c

This command brings alot together and show you the power of unix. So many powerful tools, piped together to do something great!
Last week was a bit chaotic in part because of technical issues, in part because of the variety of backgrounds you've had. But now I think we're all on the same page about more or less what the unix command line looks like, and can appreciate the beauty of it. So without further ado, lets run that command and see something beautiful.

The output is 33. Why???

md5sum returns a 128bit hash of a file. We extract just the hash from the md5sum command with the "cut" command. Then we pipe the hash to wc -c and see 33 characters! Well, the hash is dumped in hex, and how many hex characters to a byte? 2! Do you know why? Well this is very important, so I may add that to an exam. Maybe we'll do the math of why, but that just arithmetic, but it is essential computer science knowledge if you are working with bytes.

So why are there 33 bytes and not 32?? There is a newline character on the end!

try this command, not an essential one, but useful - the more you know! -
md5sum lecture.txt | cut -c1-32 > log
cat log
hexdump -c log
