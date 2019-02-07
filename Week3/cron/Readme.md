# cron

## Introduction

cron is used for getting jobs to run at a specified time in the future. A popular use case
for cron is system backups. If you are a system administrator, or just concerned about the data
on your machine at home, you may run a cronjob at 12 Noon every sunday. You would add a cron job
for the root user such as:

```
* 12 * * 0 tar -cvpzf backup.tar.gz --exclude=/backup.tar.gz --one-file-system / 
```

You can add cronjobs with the crontab command. We will look into the meaning of the above 
command now.

## crontab

Some commonly used flags for cron are `-u`, `-l`, and `-e`. `-u` runs for a particular user. `-e` means edit. 
`-l` means list. Without `-u`, the cron command is run for the logged in user.

To add a cronjob for the currently logged in user, you can run `crontab -e`.

Then, say you want to create a file containing 'hello world' at a specified time. What is the current time?

```
$ date
<Time is Shown>
```

Now type `crontab -e`. The Cronjob is specified as:

```
# * * * * * command
# Where the stars represent, in order:
# minute (0-59),
# hour (0-23),
# day of the month (1-31),
# month of the year (1-12),
# day of the week (0-6, 0=Sunday)
```

And so, if we want to run the file creation command a few minutes from now, we'll just add a line like this
to the file opened by crontab -e:

```
[current minute plus 1] [current hour] * * * echo "hello world" > ~/helloWorld.txt
```

The crontab command is for editing the crontable for a user. Every user has a crontable.

The crontables are usually stored in `/var/spool/cron/crontabs`, though you are not meant to edit them directly.
You will need root access to look at the files in there, e.g.

```
sudo ls /var/spool/cron/crontabs
sudo cat /var/spool/cron/crontabs/root # if the root user has a cron table.
```

If you want to look at your contable, you run `crontab -l`.

If you want to see another user's crontable you run `crontab -l -u $USERNAME`, but you will need root permissions to do this.

If you want to create a cronjob that requires root permission, e.g. create a file under `/root`, then you need to put it in the root crontab.

```
$ sudo su -
$ crontab -e
# Then put the appropriate cron job.
```

--Provide 3 minutes for class to create sample cron jobs and verify that they work--

How does cron know to run at a certain time? How does it stay aware of the system time? cron is a daemon, a word we learned last week. cron sits running in the background, detached from the work you may do in your system. It sits there running, checking the clock periodically to see if it needs to do some work. There is no magic to cron, as with all the other tools we use. It is simply a program.

You can download the source code of the internet with `apt-get source cron`, look at it to see how the program works, modify it, compile it, and install it on your system if you want.

Depending on your system you might have the Paul Vixie's cron program installed, or you might have Matt Dillon's crond installed as your cron daemon. You can see where cron is installed with `which cron`. You can see that cron is running by typing `ps -e | grep cron`.

## cron logs
You can view your logs to see the output of your cron jobs in `/var/log/syslog`, or, on a systemd based system, you can also run `journalctl`. You can grep in these results for cron, i.e. `cat /var/log/syslog | grep -i cron` and `journalctl | grep -i cron`.

If you try to run an impossible cronjob, e.g. the user doesn't have the proper permissions, there are many ways for you to configure the system to let you know about the errors. Consider the case where you want to run `echo hello > /root/hello.txt` from a cronjob for a non root user. This will generally write an error out in your terminal! Try it.

```
nonRoot@server$ echo "hello" > /root/hello.txt
Blah blah Permission Denied: Blah blah
```

You can configure cron in a number of ways to log the error. One way is to have cron send you an email. 
We'll use postfix for this.

```
apt-get install postfix
```

Then select the local option.

Then configure an impossible cron job.

Then look in `/var/spool/mail/USERNAME`. You will see the error there. With proper configuration this will be sent out to a supplied email address.Configuring the machine to do this is an exercise left to the reader. If there is time we may cover it later, but suffice it to say that it is possible.

## at command. 
I've seen the at command less in the wild than the cron command. Still, you may be asked about it in interviews, or may wish to use it for something or other. There are a variety of ways to use it. I'll just show you one. 

(at might not be on your machine. `sudo apt-get install at`)
```
at now + 1 minute <Enter>
echo "hello" > helloWorld.txt <Enter>
<Ctrl + D>
```

You can list the running at jobs on your machine with `atq`

## References

A couple of solid, simple references for learning about cron are:

1. https://www.linuxjournal.com/article/1189
2. https://www.youtube.com/watch?v=7MFMnsnfBJs

An article about backing up your system:
1. https://help.ubuntu.com/community/BackupYourSystem/TAR

An article about tar
1. https://www.tecmint.com/18-tar-command-examples-in-linux/
