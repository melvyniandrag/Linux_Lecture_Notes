# Introduction

Secure SHell. A secure way for connecting to remote machines. There are many interesting 
tricks you can do with ssh aside from just getting a terminal window opened.

# Class activity.
Start two cloud machines. I'm going to show you how to use ssh to connect from one to the other using the command line in Linux, and show you a little bit about how to configure your machines.


# /etc/ssh/sshd_config
Configuration file for your ssh server. For example:

You can edit whether or not you want password logins by editing the line 
```
PasswordAuthentication yes
```

You can change the port your server is running on by changing the line
```
Port 22
```
22 is the default port.

# Server <-> server 
Use ssh to connect two cloud machines

# sftp
Secure file transfer protocol. Send get/send some files between cloud machines. I think on windows you need  tool like winSCP, but I'm not sure I haven't had a reason to use windows for this kind of task yet.
