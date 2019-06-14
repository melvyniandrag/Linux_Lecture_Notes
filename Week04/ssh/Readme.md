# Introduction

Secure SHell. A secure way for connecting to remote machines. There are many interesting 
tricks you can do with ssh aside from just getting a terminal window opened. In this class I'm going to refer to two machines - one we'll call the server, that's the machine we want to connect to. The other is called the ( ask for audience participation ) client. The client wants to connect to the server. This is a standard thing in computer programming / networking. Your web browsers are clients that want to connect to web servers. Your head phones are bluetooth clients who want to connect to your bluetooth server ( smart phone ). You now have two machines, one is an ssh client, the other is an ssh server.

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

but what's the password?!?! We don't know. There is a default password/no password vconfigured for the user by default on the google cloud machine, I'm not sure what it is. I could google to find out what the default password is, or if the passwrod is disabled by default or whatever. But I don't need to, I know how to set the password and that is the path of least resistance for me. Do you remember how to set the password?

```
passwd
```

now set the password for the user you are logging into.

ahhhh but it wants the current password and we don't know it!!

let's use sudo

```
sudo su -
passwd melvyniandrag
```

then login with ssh. Notice that you don't need to 

```
sudo service ssh restart
```
because we are changing a password, that is managed by a different system on the machine, not by  the ssh daemon.

Then when we're in, poke around a bit and see that things work. Log out, log back in. 

Change the config file to prohibit password based login, then change it back. Show that it works / doesn't work.


# sftp

Secure file transfer protocol. Send get/send some files between cloud machines. I think on windows you need  tool like winSCP, but I'm not sure I haven't had a reason to use windows for this kind of task yet. sftp is a file transfer protocol ( ftp ) that runs on top of ssh. To use it go to your client machine and sftp into the server machine. Same command as before, but this time we use sftp instead of ssh.

sftp melvyniandrag@xxx.xxx.xxx.xxx

Then we can get files from that machine with 'get'. We can put files there with 'put'. On the server machine, make a file in the home directory. 

```
echo "hello" > file.txt
```

Then on the client machine

```
sftp melvyniandrag@xxx.xxx.xxx.xxx
get file.txt
exit
ls
# file.txt is there!
```

There are similar tools on other operating systems. As I said, windows has scp, I use a program called mobaxterm that has a built in scp like thing. Mac might support sftp, I'm not sure. If anyone has a mac, try to sftp into your cloud machine and get a file.

# other things you can do. ( Skip this in class until the end, if there is time. I foresee this being a huge time sink )

You can change the port your server is running on by changing the line

```
Port 22
```

22 is the default port. Change that line to put ssh on port 1122. Then try to ssh in as before. 
