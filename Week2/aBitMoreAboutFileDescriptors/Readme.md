Now lets start talking about something that always comes up when discussing linux. "Everything is a file". Throughout the course of this class we're going to see that in many ways! For example, look in you current directory. 

```
ls
```

you see a bunch of files, right?  a bunch of paths, right?

Well, type `which bash` and you'll see which bash you're using. type `which python` and you'll see which python you're using on your machine. Type which `gcc` and youll see where one of the C compilers is on your computer. It looks just like a file!


Is stdout/stdin/stderr a file? Yes. Let's write a python program that runs forever. In this class we're going to talk about linux processes, lets get a taste real quick.

```
#
# runforever.py
#
import time
while True:
    time.sleep(100)
```

Here is a python script that will run forever, okay? If you don't write python, it doesn't matter. This is a program that will run while True - thats a common programming idiom for "run forever". and forever it will sit there and read stdin. Lets run this "in the background" - more on that in just a minute. for now we just know that it will run in the background and give control of the terminal back to us.

Lets get the pidof the process - actually putting the job in the background tells us the process id of the script. We need the pid so you can do stuff to the process, as we saw before.

```
$ python runForever.py &
[pid]
$ kill -9 $pid
$ pidof python
```

see? Its dead now. There's much more you can do with the pid as we saw before. I'm going to blow your mind now, and show you more about how everything is a file in linux, we're going to take a little peek in the operating system. All linux processes have at least three file descriptors. They have three channels for communicating with the outside world. These channels were given numbers, do you remember? They are 0, 1, and 2. The 0 file descriptor is for input, the 1 is for output, and the 2 is for error output, that's just how it is.

Let's restart the python script in the background.

```
$python runForever.py &
[pid]
```
Now lets go to the following directory:

`cd /proc/PID/fd`

and don't cheat!! Just cd to the directory and don't do anything else. NOTHING!!! NO CHEATING!!! 
Can you guess what fd stands for? Ill tell you one more thing as a hint. All unix processes have at least three associated file descriptors. What does fd stand for?? And everything in linux is a file. So if you were, hypothetically, to look at the files that are associated with the three fds for process PID - /proc/PID - what do you think the files would be called?? They ought to be called 0, 1 and 2. There might be more, but those should be there. Type ls and have a look!

There are three file descriptors! That was pretty deep, and I expect you to be somewhat astounded if you aren't familiar with sort of thing. I was truly amazed when I heard of these topics and it just goes to show you that linux is beautiful, mysterious, powerful, intriguing, etc..
