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
#!/usr/bin/python

import time
with open('/opt/hello.log', 'a') as fout:
  while 1:
    fout.write("hello world")
    time.sleep(10)
```

Make the file executable

```
chmod 777 /opt/hello.py
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

you can stop the service too with `sudo service hello stop`. Then check the status. Then reboot. Then check the status. 
Do you think, before checking the status, that the service is stopped or is running? [get an asnwer] the service is running. 
Because it is enabled. You can disable the service and reboot. Try that now and verify that it works.
`sudo systemctl disable hello`. Then reboot, then check the status.

You can view the logs for your service wth journalctl:

```
journalctl -u hello
```

or just look in the rsyslog file

```
cat /var/log/syslog | grep first
```
you'll see in either case the text from "Description" from your hello.service file.

## A look at other systemd services
You can look at the other systemd service on your computer with
```
sudo systemctl list-unit-files --type=service 
```

You can see the disabled ones with 

```
sudo systemctl list-unit-files --type=service | grep disabled
```

and the enabled ones with 

```
sudo systemctl list-unit-files --type=service | grep enabled
```

You should notice that there is a cron.service there - we already played with cron in this class. You know that there is a cron daemon process running on your machine. Take a look at it!

```
ps -aux | grep cron
````

This daemon was started by init - by systemd, and now you see how it's done. You should see the service you created in the list of enabled service too ( or disabled if you disabled it! )

## The service vs systemctl tools
You have noticed me using the `service` and `systemctl` tools interchangeably while managing services. Service is a wrapper 
around systemctl. systemctl is part of systemd, but service is available regardless of the init system. Have a look at the 
code for service:

```
sudo su -
which service
vim /path/to/found/service
```

have a poke around the file. Notice that service is not a binary, it is a shell script. With enough time to think about it
, you all know enough now to be able to pick thorugh the service script and understand what it does! I'd bet in January at 
least you wouldn't even recognize it as a shell script, but at this point you probably can, you might see there are a few 
functions inside, etc. You can even tell which interpreter it runs against!

Anyway, search in that file for 'upstart', 'sysvinit' and 'systemd' and you'll see that the script does different actions depending on which init system it finds on your machine.

A weird thing is that the parameters to service/systemctl are reversed. You write:
```
service SERVICENAME ACTION
systemctl ACTION SERVICENAME
```
weird. This could be changed if you wanted.

## In depth with systemd
The main things you are going to be interested with systemd are services, as I've showed you, and targets, as you've seen multi-user.target already. Targets are collections of services. You use the WantedBy and RequiredBy fields in your service files to specicy dependencies and link services together into targets. Also look at the multi-user.target file and note the various components of it.

See section 4.2 #3 from here:https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html
Why is it good that you are learning a little bit about systemd? You may need to use this knowledge in the future to do
software installs on your Linux box! There is a cool language called CUDA that does parallel computations on your 
NVIDIA GPU. The language installation procedure requires you to change the mode that your computer runs 'init' so that 
graphical components aren't run during GPU software installs. You can check the link above. This is just an example of the
most recent time that I needed to play with my init configuration.

Notice that the instructions say to boot to runlevel 3 - there is no runlevel 3 with systemd, and we'll talk about that now, 
and see what they ACTUALLY meant.

Focus on the symlinks on page 389 of the handout. See how there is no runlevel3 on systemd, but that runlevel 3 corresponds to a systemd target. Then focus on the image on page 388 of the handout that shows the order of event for systemd. 

## Compare systemd to sysvinit
As we mentioned before, there is another init system that some members of the Linux community love and they wish that it hadn't gone away, and that system is sysvinit. I wanted us to use this init system in class so you could get used to it, but all of the distributions offered by google cloud run either upstart or systemd. I also didn't think it was worth it to put time into studying upstart because you'll likely never use it.

To be brief I'll just say that sysvinit ran bash scripts serially - one at a time  - to bring your system up. You specified run levels that signified differnt things. As you can set up systemd with targets that specify which services are run, sysvinit used runlevels. The fact that sysvinit ran scripts one at a time instead of doing them in parallel is a criticism against sysvinit.

## Another example of a systemd service.
The service doesn't need to stay alive, it can just run and end. The example we did above contained a `while 1`. We can just 
write a bash script that executes on boot. Do that together in class and verify that it works.

## Another example
Write a service that targets graphical.target and show that even if it is enabled ,it wont run at boot because we don't boot to a graphical interface.

## Pros and cons sysvinit vs systemd
https://www.slant.co/versus/12956/12957/~systemd_vs_sysvinit

## Question
I forget how to change the target the machine boots to - how do you set it? There is a systemctl option I believe, but there might be a config file you can manually change.

## Question Number 2
I don't know what happens if you introduce a circular dependency into systemd. If you make service a depend on service b and service b depend on service a, what happens? Seems to be info here -> https://unix.stackexchange.com/questions/193714/generic-methodology-to-debug-ordering-cycles-in-systemd

## References, Other Reading
1. init - https://www.linuxjournal.com/article/3109
2. service vs systemctl https://askubuntu.com/questions/903354/difference-between-systemctl-and-service-commands



