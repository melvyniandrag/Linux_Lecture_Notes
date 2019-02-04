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

### chmod



### chgrp

### Hint at something more
Stickybit, setuid, setgid.
[ Not discussed in this lecture, this is for later ]

## User limits

No time to cover this now. You can configure your system to limit the resources (e.g. cpu load, ram usage) available to a particular user.
