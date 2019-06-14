# Standard out, standard err, standard in 

All linux processes have at least 3 "file descriptors" or communication channels with the outside world. Does anyone not know what they are? Then Ill tell you. You have standard in, standard out, and standard error. We've already begun using them in this class briefly with the > operator. 

Open vim and create a file. Type a couple of words in it, we're going to use that file for the next exercise.

`wc fileThatExists > log` You see nothing. Running cat log will show you the output of the wc tool

`wc filethatdoestexist > log` You see an error in the shell, cat log shows nothing. There was no std out of wc, but there was err output

`wc filethatdoesntexist 1>log 2>errLog` Now there is no error on the screen, but cat errLog shows the error from wc.

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

<Ask for examples from other programing languages>

```
# put the following in a file and run it
# call this output.py
import sys

sys.stdout.write("I go to standard out")
sys.stderr.write("I go to standard error")
```

```
python output.py 1>log 2>errlog
cat log
cat errLog
```

Notice the missing newlines here. Just a curiosity. 


Wait - you don't see the lack of newlines?!?! Try this then.

```
$python output.py 1>log 2>errLog; cat errLog | wc
0 5 20
```

We saw before there were newlines appended to the outputs of md5sum and echo.

As an aside look what vim does to the files. Not essential stuff, but this is just to deepen your knowledge of vim and how much attention to detail is required in programming. What if you are working on a project and there is a datafile that shouldn't have newlines. Then you peek in the file with vim and absent mindedly close it with :wq. You could cause an error that could take days to debug!!

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

`$wc 0< file > log`

Also, don't forget about "append" vs write when it comes to the stderr/stdout stuff

```
$ wc filethatdoesntexist 2>> err
$ wc filethatdoesntexist 2>> err
$ wc filethatdoesntexist 2>> err
$ wc filethatdoesntexist 2>> err
$ cat err
```

You'll see alot of error messages logged in "err"

An aside, maybe you're interested? How to pipe standard error?
https://stackoverflow.com/questions/1507816/with-bash-how-can-i-pipe-standard-error-into-another-process

A common thing you'll see and maybe want to do is make your processes shoosh! If a process is running and giving alot of output you don't want you can throw away the output channels.

```
$ wc f 2>/dev/null 
```

A common place to send unwanted output is to /dev/null, it just writes your output to the ether and you don't see it and it isn't logged anywhere.

The above command should give an error, but you won't see it, its just gone. There are many times you'll want to do this. I won't dream up some big situation right now to illustrate this to you, just know you'll see this all over the place in bash scripts and there will come a time, if there hasn't already, where you'll just want to throw away either stdout or stderr and never hear about it.

Now lets talk about processes.
