# The Filesystem Hierarchy Standard.

The filesystem hierarcy standard. Specifies some standard directory layout for Linux systems. 

Look at

```
man hier
```

Some examples for each directory:

/ - look at all the directories. Suggest starting instances of multiple distros in the vm to see how they are the same.

/bin - programs needed for single user mode, for bringing a system up in maintenance mode. I've never had to do this for maintenance, but the utilities it provides are simple standard commands like `cat`,`ls`, etc.

/boot files to be used for booting the system. These are low level things you won't worry much about as a general desktop user, application developer, or web programmer. This is lowlevel stuff for getting the OS up and running between the time you plug it in and hit the power button and start using Linux. You'll see the Linux kernel, the bootloader (on your system youll probably see grub, but on an embedded project you'll probably see uboot. ) We'll compile the kernel in this class and maybe poke at the bootloader, but it might be more instructive to poke at the bootloader of a physical pc sitting in front of you.

/dev - devices and things. you'll see your harddrive/sdd for example as something like /dev/sda. There are a bunch of ttys. What a tty is and how you use it is of particular interest to me, and maybe during office hours Ill show you some stuff I do with those devices.

/etc - config files. We already configured ssh last week by messing with a config file in here.

/home - user home directories. Your homework will be to put this on a separate physical drive. This is where users put their data. Photos, downloads, video games, etc.

/lib - libraries for booting the system and used by programs on your computer.

/lib<qual> Youll see 32 and 64 bit variants of the various libraries. If you don't know what "dynamic" vs. "Static" linking means, and have never used static vs dynamic libraries, this will be outside of your understanding.

/media - where auto mounted media goes. When you stick a usb stick in, or a CDROM, it will generally appear here.

/mnt - where you will manually mount filesystems for your use. We'll explore some use cases of this today.

/opt - a place for "add on packages". Stuff you want to install goes here. The use of this directory is debatable and I leave it up to you to decide what you put here and what philosophical stance you choose on what ought to go here.

/proc - we already looked at this when we looked at stdin/stdout/stderr. We'll revisit that quickly. Write a little python program:

```
while True:
    pass
```

Run it in the back ground

```
user@machine$ python program.py &
[outputs pid]
user@machine$ ls /proc/$pid/fd
0 1 2
\
```

you see the file descriptors for stdin, stdout, stderr. the /proc has information about running processes. There is much more to see besides the file descriptors, but thats the only example I'm going to provide.

/root - the home direcotry for the root user. The root user doesn't get a directory in /home.

/sbin - programs for booting and maintaining the system, but not used by regular users. https://ma.ttias.be/understanding-the-bin-sbin-usr-bin-and-usr-sbin-split/ 
http://landley.net/writing/hackermonthly-issue022-pg33.pdf

the difference between sbin and bin has history behind it, and I've linked a few quick and interesting reads explaining the differences.

Do take a moment to 

```
ls -l /sbin
```

 and notice that many of the commands there are actually links to the commands in /bin. What's a link? In general it's like a windows shortcut. The actual program isn't in /sbin, it's in /bin, but when you call the one in /bin, it calls the one in /sbin. `bash` isn't linked, however, bash is in /bin you'll see. 

```
$ which bash 
/bin/bash
$ ls -l /sbin/b*
# bash is not there
```

doesn't matter, just showing you.

/srv - I haven't ever used this. It might be relevant to you, I don't know

/sys - don't worry about it

    /tmp - temporary files. Depending on the distro you use these might or might not be deleted on reboot. They might be cleaned up before reboot. They are temporary files, and the longevity and uses of them differs and depends on you.

For example, 

```
ls /tmp
# some stuff about ssh
```

that's temporary info about your ssh login. Don't worry about the details. 

/usr - another location for executables, libraries, etc, typically read-only stuff that isnt essential to booting the system. There's alot of argument about what goes in here. If you're a sysadmin or linux application developer you will work on this.

Notice that tmux isn't essential to your system. 

```
$apt-get install tmux
$which tmux
#/usr/bin/tmux
```

If you want to feel confused for a bit, look at this post:


https://unix.stackexchange.com/questions/8656/usr-bin-vs-usr-local-bin-on-linux

people discuss the uses of /bin, /sbin, /usr/bin, /usr/sbin, /usr/local/bin, ~/bin, etc.


It hasn't mattered to me in my career what goes where, but depending on the depth you go into Linux you may develop a passionate opinion.
