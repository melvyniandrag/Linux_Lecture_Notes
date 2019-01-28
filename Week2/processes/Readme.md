# Linux Processes

##Intro

In this section we're going to talk about processes in linux. Processes are just running programs.
When the operating system starts up there is a process called init that brings up all the other processes on the system and lets you do work.
Subsequently started processes get a new process id that uniquely identifies them. We've already seen that the the python program we ran got a process id.

```
#check out
pidof init
```

this is a very interesting and controversial process in linux, especially now. We're going to study the init process in great detail later, but I'll give you some foreshadowing - there is a culture war going on right now as we speak about this first process started by the operating system. Some people say its too complicated, some people say it's too crude, some people say the NSA is spying on us via this init process - we'll talk about that later. In any event, its pid is 1, and all the processes started after it have a higher pid.

You can see a list of all your running processes with the very helpful 'top' command. There is another similar program called htop. Check it out.
exit top/htop by typing 'q'. In the top menu you can see the pid, the user who started the process, the memory and cpu usage of the process, the name of the command that started it, how long the process has been running and more. You already know how to get the pidof a running program by typing pidof program name. Start multiple python programs and then type pidof python, and you'll see a bunch of them. 

```
python program.py &
python program.py &
python program.py &
pidof python
100 200 300
```

Then it's up to you as a programmer to determine which one it is you're after! For example, if you want to write to the standardin of a particular program, youll need to know the pid of that particular program. Thats up to you as a skilled linux programmer to know how to get the pid of interest, and we're going to look at more tools to help you do that!

A job is a process started by a shell that doesn't detach. That is, it's there held onto by the shell. If you start a program in the shell, it's held onto by the shell. Do you know the computer science word for a detached process? Ten points for gryffindor if you know how to pronounce it right! This is just vocabulary you need to know - its a daemon process. The `jobs` command lists non-daemon processes! For example, type "jobs" - youll see the three python programs you just started. If you close your shell now, and then click the ssh button again, then type jobs again, youll see they aren't there anymore. Those processes / jobs were tied to your bash shell and when you closed it they all died.

Now here's a superuseful command. If you are running a numerical simulation, for example, and want to compute the value of pi, for example, you say

```
nohup python program &
```

Now type 'jobs' and you'll see its not there. There is more to be said about this, and if you come to office hours I can show you. The job is detached from you and stays running even when you leave the shell.

You can send commands to a running process to stop and start it if you want. You can switch the running programs from running in the foreground to running in the background.

But before we get ahead of ourselves, lets talk about something you are going to do every single day. This is essential, and we talked about it briefly in the last class when some folks asked about it, and I had to fight my urge to start talking about it so I just brushed it off.

Ctrl+Z is to stop a process, ctl+C is to kill it for good, to terminate it. Stopped jobs sit there and wait for you to start them up, killed jobs are done for good. Very important. Don't forget this! Lets look at a little example. There is a python script called "incrementNumbers.py" here, we will start it and put it in the background. First lets look at it and see what it does - the script will just write a number to the terminal every few seconds.

```
import sys
import time

x = 1
while( True ):
    sys.stdout.write("{}\n".format(x) )
    x += 1 
    time.sleep(2)
```

When we run the program with python incrementNumbers.py, well see that it starts periodically writing a number. We can sto pit with ctrl + z
Then when we type jobs, we see it is a stopped job. We can bring it back into the foreground with fg % jobid. Now we can stop it again with ctrl+z. Now we can send it to the background with bg %job id. The job will keep running, but now we have control of the terminal. but its periodically bothering us with its output. We can stop it again with kill -STOP pid or kill -SIGSTOP or kill -SIGTSTP . There are difference between these, but we won't go into it just yet. To see all of the kill signals have a look at `kill -l`.  To resume it type kill -CONT pid

As an experiment now, start a python incrementNumber process and let it get to 2. Then stop it with ctl + z. Then start another and let it get to 10. The start the first one with fg %1. Then stop it with ctrl + z. Then start the second one with fg %2. See how they pick up where they left off?

----------ps---------------
Here is a real powerhouse for dealing with processes.
https://shapeshed.com/unix-ps/

ps gives the processes in the current shell. 
type
ps
then start a bunch of these increment number programs and send the output to /dev/null

python incrementNumbers.py >/dev/null &
python incrementNumbers.py >/dev/null &
python incrementNumbers.py >/dev/null &
python incrementNumbers.py >/dev/null &
python incrementNumbers.py >/dev/null &
python incrementNumbers.py >/dev/null &

ps

now you see all the processes associated with this shell
pkill python to kill them all at once. We saw some signals before like STOP and CONT, pkill sends the -SIGTERM signal which is signal  ( which number?? - ask class. remind to use kill -l) #15, and not the dreaded #9. More about these signals in a second, we already saw a few before but, as always, theres much mre to say.

now ps again
they are eigther gone, or reporting that they have been terminated.


To see all the processes running on your system type:

either 
ps -e
or 
ps -aux

to see processes by user ps -u USERNAME. For example, try ps -u $(whoami)

to see processes by group ps -g GROUPNAME - but whats a group?? We'll cover that in a few weeks.

Exercise:
How many processes am I running? 

ps -u melvyn | wc -l

How many root processes are running? 

ps -u root | wc -l

This is important information about running processes on your machine that can be used for all kinds of system administration tasks.

One more funny thing  I thought to do with the top command, talking about processes. Lets make a real resource hogging process and see it being greedy with top

```
while(True):
    pass
```

returning to our discussion about about the terminate signals, we saw two ways to kill a process. One was with CTRL+C before and now we say pkill program name ( which kills all instances of th eprogram). You can terminate a program with the kill signal with 

```
kill -KILL pid
kill -TERM pid
```

pkill sends the term signal, which is signal number 15. Ctrl + C sends the signal SIGINT, signal number 2. You may notice that if you try to Ctrl + C a program it doesnt respond. sigint tries to interrupt the process and says "excuse me, you should stop now". But sometimes you need to be more direct so you send the sigterm -TERM signal, signal number 15, as with pkill. But sometimes the process just wont listen so you bring out the bazooka and blast it with the -KILL signal, the dreaded number 9. How the process / operating system goes about handling these signals is interesting and will be discussed later if we have time to write a simple program to handle signals, but we probably wont have time. You'd need to grab a book on C programming and look into signal handlers.

https://gist.github.com/aspyct/3462238 Here is an example of a sample program that has signal handler logic in it. You can see that the programmer has written the program to behave in different ways depending on the signal it receives.
