# Signal Handling in Linux

## Introduction
In this class we're going to look at signal handlers.
We already saw that we can send signals to a process with a 
keyboard. Specifically, we can send the `SIGINT` signal to a process
with `CTRL+C` which aborts a process, SIGINT can cause a process
to end completely.

We'll use this simple process as an example:
```
$ cat program.py
import time
while True:
    time.sleep(1)
$ python program.py &
[PID]
$ <TYPE CTRL+C>
#Process exits
```

We can also send the `SIGTSTP` signal to a process with `CTRL+Z`

```
$ python program.py &
[PID]
$<TYPE CTRL+Z>
#process stops
```

These stopped processes can be restarted by sending them a CONT signal.

## The kill Command
You can use `kill` to send a signal to a process. For example, to make
a stopped process resume execution.

```
$ kill -SIGCONT $STOPPEDPID
```

You can see all the signals you can send by typing `kill -l`. You can send these signals in three ways - you can type the signal name, the signal name prefixed with `SIG`, or you can send the signal number. 
For example, to send the CONT signal you can send:

1. `SIGCONT`
2. `CONT`
3. `18`

In this lecture we're going to focus on `SIGINT`, `SIGKILL`, `SIGTERM`, `SIGSTOP`, `SIGTSTP`, and `SIGSEGV`. In particular, we're going to look at when you should use each one, and 
how programs handle the signals when they are received! These are 6 of the most interesting of the 64 signals shown by `kill -l`, and they serve to illustrate key points about signal handling.

We'll play with the signals a little bit more before we start coding.

```
$ python runForever.py &
[pid]
$ jobs
[1]+ Running     python runForever.py &
$ kill -20 %1 # kill takes pids or jobs. You could also put the [pid] from above
$ jobs
#stopped
$ kill -18 %1
$ jobs
# it's running again
```

We just sent SIGCONT and SIGTSTP. We can also send a signal related to TSTP called STOP.

```
$ python runForever.py &
[pid]
$ jobs
[1]+ Running     python runForever.py &
$ kill -SIGSTOP %1 
$ jobs
#stopped
$ kill -18 %1
$ jobs
# it's running again
```

## SIGINT, SIGTERM and SIGKILL
`INT` is sent when you hit `CTRL+Z` on your keyboard. It interupt the process and makes it stop. `SIGINT` can also be sent will `kill`. `SIGTERM` and `SIGINT` are approximately the same thing, differences in their behavior are left up to the application developer. You should now send `INT` and `TERM` to the `runForever` program and you will see that both end the process. 

We will change the behavior now. Open `int_term.c` on your computer and have a look at it. ( Look at 01_*.c with the class and point out the cusom signal handlers. Also, as an added bonus not relevant to signal handling, notice that there are different return codes in the code. Run the code. From a separate terminal window, send kill signals. Then inspect the return code of the running process and see how we customized the return valu based on which signal we received. Remember that in our first assignment we looked at $? to see how a program ended. You can return different values not just fro mbash scripts, as we've done with `return` and `exit` statements up until now. Your software can be programmed to return values too.

Returning to our discussion of signals, signals can be caught,  ignored, or blocked.

We will play with the 02*.c and 03*.c code here to see the difference between ignored and blocked signals. Experiment for 5 minutes or so until we are comfortable we understand the difference.

Notice that you can always send signal -9, no matter what is happening this signal will work. It cannot be blocked or ignored! In any Linux system administration book you read you will see the 
warning: `NEVER USE -9!`. We have just seen that processes can deliberately ignore or block signals if interruption would cause some serious system harm. As such, only use SIGKILL under very dire circumstamstances, becuase issuing tihs signal could cause file corruption!

Actually, thats what they say.

Let's read and laugh at the reasons say not to use SIGKILL in the following posts:
https://www.reddit.com/r/linux/comments/4b1mwh/do_not_use_sigkill/
https://unix.stackexchange.com/questions/281439/why-should-i-not-use-kill-9-sigkill
http://turnoff.us/geek/dont-sigkill/

People above say things like "kill -9 is pulling the rug out", but no one provides a single concrete example of something going haywire with 
kill -9. "weasel words".

The counterculture:
See borud and dbrower
https://unix.stackexchange.com/questions/8916/when-should-i-not-kill-9-a-process


I don't know. I'm not terribly opposed to using kill -9. You develop your own opinion. I will generally try the gentler kill signals first and only in the end resort to kill -9.

Though I don't know all the signal numbers by heart, I always have to look at the kill -l table to see what my options are.

## SIGSTOP and SIGTSTP
About the two:
https://stackoverflow.com/questions/11886812/whats-the-difference-between-sigstop-and-sigtstp

you can ignore the SIGTSTP that is sent from the keyboard. There is no ignoring the SIGSTOP command, however.
See stop.c. All we do in this program is ignore the signal. Handling a tstp is slightly more complex than handling a process termination. 
You need to provide a way for the process to come back to life.

```
#go through a few iterations of this

#try ctrl+z - does nothing
kill -SIGSTOP $(pidof a.out)
kill -SIGCONT $(pidof a.out)
# a few times
#finally
kill -SIGTSTP $(pidof a.out)
#nothing
kill -SIGKILL $(pidof a.out)
#done
```

## SIGSEGV
This is the seg fault signal. This happens on x86 architectures when an invalid memory access is made. For interesting examples of code that causes this signal, check out:

1. https://codegolf.stackexchange.com/questions/4399/shortest-code-that-raises-a-sigsegv
2. https://stackoverflow.com/questions/18986351/what-is-the-simplest-standard-conform-way-to-produce-a-segfault-in-c

The simplest example that causes a segmentation fault is the program 

```
$ cat main.c
main;
$ gcc main.c -o main
$ ./main
```

## What are signals?
Signals are a form of interprocess communication used in Linux. There are many interprocess communication mechanisms, this is just one of them. If you've never heard of IPC, just know it is all around you when you are using computers. For example, consider the case when you are on your telephone and you're listening to music. When a phone call comes in, the music is probably paused and the phone app is brought up on the screen. The operating system on your phone needed an IPC mechanism to detect that the phone process was in some active state and that other interfering processes need to take action while the call is active. Depending on how the software is written on your phone, the music might resume playing when you hang up, and the music app might come to the foreground on your screen. Or maybe it stays paused and you have to manually reopen the app and hit 'play' again. Or maybe something else happens.

IPC might also be used if you have two processes on a device - maybe you have one process listening for radio transmissions and another on that turns a motor. If the radio receiver receives a signal, maybe you want another process to turn a motor and open your garage door or something.

There are many ways to do IPC, even on Linux there are a bunch of IPC mechanisms. Signals is just one of them.

## Who sends signals?
The Linux kernel can send a signal, another process can send a signal, or a process can send a signal to itself. We saw the kernel sending signals in the case of segfaults, we saw the 
