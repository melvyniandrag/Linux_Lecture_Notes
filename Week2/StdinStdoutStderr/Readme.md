# Standard out, standard err, standard in 

All linux processes have at least 3 "file descriptors" or communication channels with the outside world. You have standard in, standard out, and standard error. We've already begun using them in this class briefly with the > operator. 


`wc fileThatExists > log` You see nothing. Running cat log will show you the output of the wc tool

`wc filethatdoestexist > log` You see an error in the shell, cat log shows nothing. There was no std out of wc, but there was err output

`wc filethatdoesntexist 1>log 2>errLog` Not there is no error on the screen, but cat errLog shows the error from wc.

`wc filethatdoesntexist >log 2>errLog` You can put the 1 or not, it assumes the 1 is for stdout, 2 is for stderr.

A common "idiom" you'll see is

`wc file 1>place 2>&1` that redirects both stdout and stderr to the same location.

You can also write 
`wc filethatdoesntexist &>place` to redirect both to 'place'.

You see this in many programming languages too, like c++ gives you 
cout << 
and 
cerr <<

python gives you sys.stdout sys.stderr.

```
# put the following in a file and run it
# call this output.py
import sys

sys.stdout.write("I go to standard out")
sys.stderr.write("I go to standard error")
```

```
python file.py 1>log 2>errlog
cat log
cat errLog
```

Notice the missing newlines here. Just a curiosity. We saw before there were newlines appended to the outputs of md5sum and echo.

As an aside look what vim does to the files. Not essential stuff, but this is just to deepen your knowledge of vim and how much attention to detail is required in programming.
```
wc errLog
0 blah blah
```
There are no newlines

Not open errLog with vim and quit immediately with :q

```
wc errLog
0 blah blah
```
Now open with vim and close with wq
wc errLog

Now there is a newline! Writing with vim - vim always puts a newline at the end of the file.

Now lets move on to standard in. We've already seen alot of it. Pipes use standard in!! You can always pipe the stdout of one process to the stdin of another!

```
cat file | wc
```

The stdin of wc picks up the stdout of file! Processes can take inputs and give outputs.

There are various ways to feed a process's standardin. Some tools allow you to just give it as a positional argument, like wc.

```
wc file
```

'file' goes to the stdin of wc.

You can also be more explicit. We saw that stdout is "1" for some mysterious reason, and stderr is "2" for an equally mysterious reason. Well, not a mystery, this is just boring technical stuff. Some programmer way back when made the decision to associate these numbers with the indicated channels, and that's the way it is! Why do we type "cp" to copy a file??? Just another boring technical reason, that's how the computer program was written , right?? Well, stdin is 0. Also, output is associated with > and >>, input is associated with <

So we can also type `wc < file` or `wc 0< file`

I don't know if I've ever written this syntax, maybe once or twice. I'm an application and operating system developer mainly. It certainly isn't in my day to day work, but it's good to know in case you come across it in a script, an exam, or have to teach it!


Of course, you can mix these things

`wc 0< file > log`

Also, don't forget about "append" vs write when it comes to the stderr/stdout stuff

```
wc filethatdoesntexist 2>> err
wc filethatdoesntexist 2>> err
wc filethatdoesntexist 2>> err
wc filethatdoesntexist 2>> err
cat err
```

you'll see alot of stuff
An aside, maybe you're interested? How to pipe standard error?
https://stackoverflow.com/questions/1507816/with-bash-how-can-i-pipe-standard-error-into-another-process

Now lets start talking about something that always comes up when discussing linux. "Everything is a file". Throughout the course of this class we're going to see that in many ways! For example, look in you current directory. 
ls
you see a bunch of files, right?  a bunch of paths, right?
Well, type 'which bash'
and you'll see which bash you're using. type 'which python' and you'll see which python you're using on your machine. Type which gcc and youll see which C compiler is the default on your computer. It looks just like a file!


Is stdout/stdin/stderr a file? Yes. Let's write a python program that runs forever. In this class we're going to talk about linux processes, lets get a taste real quick.

```
#
# runforever.py
#
import time
while True:
    time.sleep(100)
```

here is a python script that will run forever, okay? If you don't write python, it doesn't matter. This is a program that will run while True - thats a common programming idiom for "run forever". and forever it will sit there and read stdin. Lets run this "in the background" - more on that in just a minute. for now we just know that it will run in the background and give control of the terminal back to us.

Lets get the pidof the process - actually putting the job in the background tells us the process id of the script. What's a process id? I said we'll go into that in depth in a minute, but suffice it to say that it's a unique identifier for the running program okay? So you can do stuff to it. You can start and stop the program with that number. Well I might as well tell you a tiny bit more about the pid really quick, okay. Lets stop the process. 

pidof python
kill -9 $pid
pidof python

see? Its dead now. There's much more you can do with the pid. Its a name we can call that running program and do stuff to it. I'm going to blow your mind now, and show you more about how everything is a file in linux. All linux processes have at least three file descriptors. They have three channels for communicating with the outside world. These channels were given numbers ,do you remember? They are 0, 1, and 2. The 0 file descriptor is for input, the 1 is for output, and the 2 is for error output, that's just how it is.

Let's restart the python script in the background.

$python runForever.py &
[pid]

Now lets go to the following directory:

cd /proc/PID/fd

and don't cheat!! Just cd to the directory and don't do anything else. NOTHING!!! NO CHEATING!!! 
Can you guess what fd stands for? Ill tell you one more thing as a hint. All unix processes have at least three associated file descriptors. What does fd stand for?? And everything in linux is a file. So if you were, hypothetically, to look at the files that are associated with the three fds for process PID - /proc/PID - what do you think the files would be called?? They ought to be called 0, 1 and 2. There might be more, but those should be there. Type ls and have a look!

There are three file descriptors! That was pretty deep, and I expect you to be somewhat astounded if you aren't familiar with sort of thing. I was truly amazed when I heard of these topics and it just goes to show you that linux is beautiful, mysterious, powerful, intriguing, etc..

Oh, and one more topic before we move on to discuss processes in more depth. 

A common thing you'll see and maybe want to do is make your processes shoosh! If a process is running and giving alot of output you don't want you can throw away one of the output channels.

wc f 2>/dev/null 

A common place to send unwanted output is to /dev/null, it just writes your output to the ether and you don't see it and it isn't logged anywhere.

The above command should give an error, but you won't see it, its just gone. There are many times you'll want to do this. I won't dream up some big situation right now to illustrate this to you, just know you'll see this all over the place in bash scripts and there will come a time, if there hasn't already, where you'll just want to throw away either stdout or stderr and never hear about it.

Now lets talk more about processes.
