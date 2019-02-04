# Introduction

Linux/Unix is a multiuser operating system. This may not seem revolutionary, but when Unix came out the concept of a multiuser machine was a big deal. Windows is also multiuser and macs run a verion of BSD ( like linux ) so this may not impress you. I'm going to show you how to add/remove and manage users now.

There is even discussion in modern operating systems of being single user! https://discuss.haiku-os.org/t/suggestion-we-remain-single-user-read-on/2031 Look at the cook haiku os!

## Users
You have already seen that when logged into a machine you login as a user - `whoami` will tell you your username. You have a home directory for storing your personal files at `/home/$(whoami)`. Users can be added, removed, and modified in your system.

### Adding Users
You add users with the `adduser` command. Try it to add a user to your machine!

```
user@machine$ sudo adduser newusername
# Then answer the following questions.
# The only two essential questions are the password questions, you can just hit <enter> to go through the rest.
```

To see that the user created, look under `/home`. You will now have a home directory for this user.

```
user@machine$ ls /home
you thenewuseryouadded
```

You don't have permission to touch edit this user's files. The permissions you have depends on the way your system is configured! For example, on
this system you can look in the user's home directory.

```
user@machine$ touch /home/thenewuseryouadded/file.txt
#error
```

but

```
user@machine$ ls /home/thenewuseryouadded
#No error message
```

And look what vim says if you try to :wq a file there:

```
user@machine$ vim /home/thenewuseryouadded/file.txt
#no problem. Now add some text and try to :wq. You will see
# something to the effect of "readonly is set"
# exit with :q!
```

To switch to using the user you created, you can user the 'substitute user' command `su`.

```
user@machine$ sudo su - thenewuseryouadded
thenewuseryouadded@machine$ whoami
thenewuseryouadded
thenewuseryouadded@machine$ exit
user@machine$
```

### Deleting Users

To delete a user you use the deluser command. This can only be run as a superuser. 

```
user@machine$ sudo deluser thenewuseryouadded
```

You may want to remove their home directory as well in one fell swoop. If you run the command above, you'll have to 

```
user@machine$ sudo rm -r /home/thenewuseryouadded
```

To do everything at once:

```
user@machine$ sudo deluser --remove-home thenewuseryouadded
```

There are other options for deluser, you can see them all with `man deluser`.

### The root user. sudo

There is a special user in Linux/Unix called root / the superuser. The superuser is all powerful on the machine and can do anything he wants. You can delete whatever files you want, install software, modify system configuration settings, tamper with the operating system - anything. As such, it is important to limit access to this user profile. If you are a sysadmin at a company you will have root access to the company machines. Other employees typically do not, to limit the chances that non professionals will ruin the software on the machine. For example, go on the internet on these njcu machine and try to download and install a program. It will ask for administrator access and prohibit you from installing software - it is the same on Linux.

There are a few ways to gain root access to your machine.

You can run:

1. ` sudo su -` to change your user to root.
2. You can run an individual command with the `sudo` prefix. e.g. `sudo apt-get install somesoftware`.

Not everyone is granted root access. Log in to the user account of the new user your created.

```
user@machine$ sudo su - thenewuseryouadded
thenewuseryouadded@machine$ sudo apt-get install software
#Asks for password
#You enter password
thenewuseryouadded is not in the sudoers file. This incident will be reported.
```

Whereas you do not get this error with the user given to you by default on the cloud machine. The new user is not a privileged user.

There are several ways to make a user a privileged user. One way is to run the following command from the account of a privileged user:

```
user@machine$ sudo adduser thenewuseryouadded sudo
```

This adds the new user to the sudo group. More about groups later.

### Changing passwords

You can change a user's password. To change your own password, run `passwd` and follow the prompts.

To change any user's password, type `passwd USER` from a privileged setting. Then follow the prompts.

## Groups
Users can be binned together into groups to allow common security measures, privileges, etc. to be applied to all the users in a particular group.

### Adding Groups

Create a group

```
user@machine$ sudo groupadd njcu
```

To verify that the group was added, lets count the available groups on our system before and after the add.

```
user@machine$ sudo getent group | wc -l
N
user@machine$ sudo groupadd njcu2
user@machine$ sudo getent group | wc -l
N+1
```

### Deleting Groups

Just as easy as removing a user.

```
user@machine$ sudo groupdel njcu
```

### Adding a user to a group

```
user@machine$ sudo usermod -a -G GROUP USER
```

or use

```
user@machine$ sudo adduser USER GROUP
```

as we did before with adding the new user to the sudo group.

### Deleting a user from a group

You can delete a user from a group just as you can add a user to a group.

```
user@machine$ sudo deluser USER GROUP
```

## Permissions

All linux files have permissions, an owner, and a group. You can see these characteristics when you type `ls -l`.

```
user@machine$ touch sampleFile.txt
user@machine$ ls -l
...
-rw-rw-r-- 1 melvyn melvyn    0 Feb  4 07:30 sampleFile.txt
...
```

The owner is 'melvyn', the group is 'melvyn' and the permissions are 'rw-rw-r--'. There is a preceding dash, we'll 
discuss that a bit later, it has very fascinating properties, but at this point in the class we aren't ready to appreciate what it does yet.

Linux/Unix do not support editing permissions for files on a per user basis. Instead, the permissions can 
be set for the owner, the group, and everyone else. In the permission bits for sampleFile.txt we see `rw-rw-r--`.
This means that the file owner can read and write ( `rw-.....` ), the other group members can read and write ( `...rw-...` ) and everyone else
can only read (`......r-0`).

### chmod
The chmod command is for changing permissions. Linux files have permission bits to specify whether they are readable, writable or executable.
There are two ways to run the command, you can pass it numeric arguments or you can pass it character arguments. For the numeric syntax, you need to remember that 

2^0 = 1 <-> executable
2^1 = 2 <-> write
2^2 = 4 <-> read

You can remember which one is which by remembering that r is to the left in the permission triplet and 2^2 is to the left in the binary representation of the number. Not sure if this helps, you can think about it to find a memorization technique that works for you. I was never taught such a technique and devised this one on my own.

So to change the permissions of a file to only readable for all users we say 

```
user@machine$ chmod 444 sampleFile.txt
```

To change permissions on the file to read and writable for the owner only, we run

```
user@mchine$ chmod 644 sampleFile.txt
```

To make the file read and writable by the owner, but deny everyone else all rights, we run

```
user@machine$ chmod 600 sampleFile.txt
```

To verify that no one but the owner has rights to this file you can log in as the other user you created earlier and try to `cat` the file now.

```
user@machine$ sudo su - thenewuseryouadded
thenewuseryouadded@machine$ cat sampleFile.txt
blah blah Permission Denied: blah blah
```

The mnemonic syntax for chmod uses characters instead of these permission numbers built of sums of 1s, 2s and 4s.

There is another 10 minutes that can be spent discussing this syntax, but I'll  just show you really quick. `u` means 'user', `g` means 'group', and `o` means 'other' in what follows.

```
user@machine$ chmod u+x sampleText.txt
user@machine$ chmod g=rw sampleText.txt
user@machine$ ls -l
...
-rwxrw---- other_information_here sampleFile.txt
```

`chmod` also has a recursive option that can be used to recursively apply permissions.

```
user@machine$ mkdir a/b
user@machine$ touch a/foo.txt
user@machine$ touch a/b/bar.txt
user@machine$ chmod -R 700 a
```

Then you can have a look inside a at the files and directories there.

We haven't written executable scripts yet, we'll take a minute to do that now.

```
user@machine$ vim firstScript.sh
user@machine$ cat firstScript.sh
#!/bin/bash

echo "hello world"
```

The first line is called a shabang line, and that specifies which interpreter to use when executing the script. We want to run a bash script.
Then we can make it executable and run it like this:

```
user@machine$ chmod u+x firstScript.sh
user@machine$ ./firstScript.sh
hello world
```

### Permissions and directories
It is pretty clear what the permissions mean for a file. read means you can read it, write means you can write, execute means you can run it as an executable program. What do permissions mean for a directory?

1. read means the contents of the directory can be listed
2. write means files can be created, destroyed, and renamed in the directory
3. execute means the directory can be entered.

```
user@machine$ mkdir a
user@machine$ chmod 700 a
user@machine$ chmod u-r a
user@machine$ ls a
Permission Denied
user@machine$ chmod u=rx a
user@machine$ cd a
user@machine$ touch foo.txt
Permission Denied
user@machine$ cd ..
user@machine$ chmod 600 a
user@machine$ cd a
Permission Denied
```

### chown
The chown command is for changing ownership.

### chgrp



### Hint at something more
Stickybit, setuid, setgid.
[ Not discussed in this lecture, this is for later ]
There are more bits that can be adjusted for files that give files interesting properties.

## User limits

No time to cover this now. You can configure your system to limit the resources (e.g. cpu load, ram usage) available to a particular user.

## Going further

For more information about these topics, feel free to read chapter 6 of the Evi Nemeth Unix/Linux Sysadmin book.
