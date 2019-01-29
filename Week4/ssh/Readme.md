# Introduction

Secure SHell. A secure way for connecting to remote machines. There are many interesting 
tricks you can do with ssh aside from just getting a terminal window opened.

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

# Putty
In this exercise we will
