# Introduction

Secure SHell. A secure way for connecting to remote machines. There are many interesting 
tricks you can do with ssh aside from just getting a terminal window opened.

# Class activity.
Start two cloud machines. I'm going to show you how to use ssh to connect from one to the other using the command line in Linux, and show you a little bit about how to configure your machines. Notice when you click the ssh button in the browser and wait for the terminal to come up in a window you see it says something about "transferring ssh keys to the machine". More on encryption, ssh, and keys later. When the instances are up I'll show you a little command I use all the time to get the ip address of my server. There  are other ways, but I learned this way a while back and this is what I do.

```
curl ipinfo.io/ip
```

Now you are wondering what the curl command is. It's for accessing websites. Kind of like how you use chrome or firefox to access websites, but this is on the command line. If you are familiar with a tool called postman, curl is more like postman than a browser. ANyway, the website ipinfo.io/ip is a website that tells you your ip address.

Before we get off the subject of websites - checkout a little site I put together ages ago and abandoned - melvyniandrag.github.io
Now that you have a github page, if you want to make a website you can. Github hosts your personal page for free, and it's super easy to get started. So you can throw up some pictures of projects you've done / links to your code and social media presence / whatever else and show it to employers, fellow academics ,whatever.

Here's a short intro into how to make your github io page https://guides.github.com/features/pages/

Anyway, now we can try to connect between the two machines.

Get the ip of one fo the machines and we'll connect to it from the other. 

ssh melvyniandrag@xxx.xxx.xxx.xxx

this command will fail due to some public key issue. We'll try to login with passwords instead of a public key.

On the server machine, open the config file

```
sudo vim /etc/ssh/sshd_config
```

You can edit whether or not you want password logins by editing the line 
```
PasswordAuthentication yes
```

Then restart your ssh server. 

```
sudo service ssh restart
```

Then try to login again from the client machine. This time it will ask you for your password, no error about Public Key stuff.


# other things you can do.
You can change the port your server is running on by changing the line
```
Port 22
```
22 is the default port.

# Server <-> server 
Use ssh to connect two cloud machines

# sftp
Secure file transfer protocol. Send get/send some files between cloud machines. I think on windows you need  tool like winSCP, but I'm not sure I haven't had a reason to use windows for this kind of task yet.
