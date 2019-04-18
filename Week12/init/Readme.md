# init systems on Linux

In this section we talk about init systems. When you hit the power button on your Linux machine, you expect to get to a desktop
GUI on your laptop/PC or a command line on your server, as we are using in this class. For that to happen, a few interesting, 
technical things have to happen. First your bios starts things up, then you drop into a bootloader like GRUB or UBoot, then the
kernel does a few things like mount file systems ( we already saw how important it is to use UUIDs for drive identification, and 
not device names like /dev/sdb2 ! ). Then the kernel runs a first process that allows all the other processes to start that allow
you to do things on your computer, like write and compile programs, surf the internet, etc.. In this portion of the lecture
we're goingto focus on that interesting bit of code, the first program that the kernel runs. This is "init", and there is a 
considerable amount to say about it in terms of technical details, *n[i,u]x culture and controversies.

## Types of init
In the Linux world there are a few init programs around. These days you will usually deal with systemd, but some distributions
will use other init systems like SysVInit and upstart. You can check which init system you are running by either running

```
sudo /sbin/init --version
```

or

```
sudo strings /sbin/init | grep -i systemd
sudo strings /sbin/init | grep -i upstart
sudo strings /sbin/init | grep -i init # I think, can't remember immediately how to check for sysvinit
```

Check out the following images to see the different init systems in use:
1. Ubuntu 14.04
2. Ubuntu 18.04
3. Debian 9
4. Centos 6
5. Centos 7
6. SUSE 15

Notice that these different distros have differnet init systems - issues like this is why video games and other cool bits of
software sometimes dont come to linux - too much variation, even amongst the 'big' distros! We also saw variations in 
awks and seds installed on our machines.

## Controversy
There is a branch of debian called Devuan that is the maintained to be as close to the mainline debian as possible, but
uses SysVInit and not systemd.
Devuan -> https://devuan.org/
Devuan isn't really a mainstream distribution so far as I know. It's probably used by a small percentage of discontented
debian users. You may find yourself as part of the group or you may not.
This is due to a bit of controversy around systemd, a loud group of people oppose systemd because of:
1. a dislike of the author, Lennart Poetering [spelling?]
2. they think it does too much - they want the init system to just start processes and get out of the way. systemd does more than athat
3. systemd stores binary logs, not text logs, and people don't like that
4. systemd was somehow or another funded by RedHat, which gets alot of US Gov't monday, so maybe the code is bugged.
5. The code is quite complex, so it is difficult to proofread.  It's here->https://github.com/systemd/systemd

To hear a great discussion of the pros and cons of systemd, check this video out on youtube: https://www.youtube.com/watch?v=o_AIw9bGogo
( The tragedy of systemd - the speaker is quite a controversial figure too and a member of the BSD community ).

You know about ASCII and UTF8 files, and I'm going to use that knowledge to segue us into the problems (2) and (3) I listed above. 
Systemd stores logs in binary format, whereas the old logging tool 'rsyslog' would store ASCII ( or UTF8? I'm not sure. Probably just ascii )
files.
The data in a systemd log does not comply with UTF8 or ASCII encoding rules, which you are somewhat familiar with now.
(all Ascii characters start with what bit? ) ( all 2 byte UTF8 code points start with what 3 bits? ). The data is compressed by some
algorithm or encoded or whatever, so it's not human readable. This is prone to errors which some people don't like. On most distros
that I've used the traditional, ASCII-logging rsyslog is still running alongside the systemd logger, journald ( the journal
daemon ).

To verify what I'm saying, try the following:

```
ps -aux | grep journal
ps -aux | grep syslog
```

And you will see both the journald and rsyslogd running ( on debian 9 at least ). To verify that journald logs binary data, 
check out `cat /run/log/journal/*/*`
you will see alot of junk come out. And then try `head /var/log/syslog` and you will see text. 

So how do you read systemd logs ( journald logs )? You use the journalctl tool. Try typing `journalctl` and you will see the log.
Exit by typing `q`.

And there's the compaing number (2) I mentioned above - people complain about the feature creep of systemd. Why is the tool that's 
supposed to just start your processes ALSO managing the logging of data. And why is it doing it when there is already a time-tested
daemon for doing that, 'rsyslogd` has been in use for a while and does a great job at logging. I'm in the camp of people
that just wants to start coding so I don't really care if I use one init system or another. Indeed, that's probably how most
people feel as systemd has made its way into debian, ubuntu, redhat, centos, suse, etc. i.e. many very popular distributions. 
There is the nagging anxiety, however . . . what if "they" are right and this is contaminated software . . . what if the NSA
is watching us . . . I've personally given up on expecting any off-the-shelf software to be without loopholes!

## Writing systemd services
There is more to the story, but to get us going let's just jump right into practical things. Sometimes you want a job to run 
when you power on your machine. For example, you want skype to turn on as soon as you boot your machine. Or you are running
Linux on your McDonalds touch-screen cash register and you want the cash register to boot right to the cash-register
application, like these: https://www.reddit.com/r/employeesonly/comments/1t6w9y/mcdonalds_cash_registers_xpost_from/.
If your computer is running systemd, you can write some systemd services / service units and have them run on boot!
In this example we'll write a little python program that just says 'hello world' every 10 seconds and logs it to a `/opt/hello.log`. We'll call this file `hello.py`.

Log in as root (`sudo su -`) and then write `/opt/hello.py`. The python code:

```
import time
with open('/opt/hello.log', 'a') as fout:
  while 1:
    fout.write("hello world")
    time.sleep(10)
```
and then ( still as root ) we need to make a service file `/lib/systemd/system/hello.service`.

```
[Unit]
Description=My first service

[Service]
ExecStart=/opt/hello.py

[Install]
WantedBy=multi-user.target
```

And then we need to start the service `sudo systemctl start hello`. Then check `service hello status`. You should see your service running. Then look at `/opt/hello.log`. Check back every ten seconds and you'll see the file growing. Then `sudo reboot`. Now when you  check the status again `sudo service hello status`, youll see it's not running. To have the service run whenever you boot, you need to enable it. `sudo systemctl enable hello`. Then reboot again. Now when you check the status, you'll be running the service.

## References, Other Reading
1. init - https://www.linuxjournal.com/article/3109



