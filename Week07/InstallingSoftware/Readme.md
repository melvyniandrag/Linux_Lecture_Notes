# How to install software

To start, a bit of trivia. Debian releases are named after toy story characters! You can see your debian release name with 
`lsb_release` -a. We are using Debian 9 in the cloud, that codename is Stretch. Reference: https://unix.stackexchange.com/questions/222394/linux-debian-codenames . Debian is famous for moving slow, releases/updates are infrequent. The distribution undergoes extensive testing and very few new software packages are allowed into the distribution at a time. Other distributions releae updates very frequently with all kinds of new code. These distributions are less secure than debian, but oftentimes easier to use because whatever softwrae you need is there, available for the distro. 

There is a testing distribution that is pending release. Right now Debian Buster is the testing distribition, it will be released as version 10 some time in the future. The unstable distribution that is even less stable than the pending release is always called `Sid`. This is just a bit of cultural knowledge for you. I'm telling you this because it's good to know, and because we'll be reading some documentation today that refers to things like `Buster` and `Jessie` and `Sid` and I want you to know what you're looking at.

In particular, we are going to look at  `curl` today. Have a look at the `curl` page https://packages.debian.org/search?keywords=curl and you'll see the code names I've just mentioned to you.

## apt, dpkg and .deb files
99.99% of the software installs I've done have been like `apt-get install $SOFTWARE`. `apt` can do more than this however. `apt`, by the way, is the package manager on debian. `apt` is used for managing software on your Debian based Linux distro. `apt` is based on the dpkg package manager. We're going to look at dpkg now. But, before we do, let's just check if we have `ghc` installed on our system. 

`which ghc`

No we don't.

The package manage on Debian is dpkg, and it's a bit of a pain in the neck to use, this is the reason why apt exists. The problem is that dpkg doesn't install dependencies for you when installing software.

Software package files are of type ".deb". .pngs and .jpgs are images, .tars are tar files, .txt are text files, .deb are debian software package files. When you apt-get install or use the dpkg tool we are about to use, the file type that is being installed is a .deb. Interestingly, iOS uses .deb files as well.https://www.lifewire.com/deb-file-2620596
https://apple.stackexchange.com/questions/221686/why-are-deb-files-used-in-ios

Let's install Haskell with the .deb:
Download page for the .deb file https://packages.debian.org/stretch/amd64/ghc/download
`wget` the file.
Then install with `dpkg -i *.deb`. You will see that it fails. You can fix the system with `apt`. `apt-get install -f`. You will see something like:

```
The following NEW packages will be installed:

  binutils cpp cpp-6 gcc gcc-6 libasan3 libatomic1 libbsd-dev
  libc-dev-bin libc6-dev libcc1-0 libcilkrts5 libffi-dev libgcc-6-dev
  libgmp-dev libgmpxx4ldbl libgomp1 libisl15 libitm1 liblsan0 libmpc3
  libmpfr4 libmpx2 libncurses5-dev libquadmath0 libtinfo-dev libtsan0
  libubsan0 linux-libc-dev manpages manpages-dev
```
What are all these packages apt wants to install? e.g. libgmpxxx, this is a requirement of ghc. apt knows what depends on what, and can find and install needed libaries, etc. to make osftawre installs happen correctly. 

Go ahead and fix the installation. Now `which ghc` will show us where ghc has been installed. Last week I showed you how to write programs in a couple of languages. I'll just take a second to have you write a program in yet another language, but this is a cool language! Something different!

`ghc` is the Glasgow Haskelll Compiler. Haskell is a so called" functional language". It's different from languages like Java or Javascript or C++. This language doesn't have for and while loops, for example, you go about coding things in a very different way! Some of the ways you do things in Haskell has slowly but surely been implemented in languages like Python and C++ and Java as people have grown fond of the functional programming style. 

I won't go into how to write functional programs, but I'll just let you write a simple program just so you know you can, and then if you want to learn more, you definitely should.

Haskell Hello world:
https://wiki.haskell.org/Haskell_in_5_steps

Put this in a file called hello.hs:

```
$cat hello.hs
main = putStrLn "Hello, World!"
$ghc hello.hs
$./hello
Hello, World!
```

These are the main commands you will use on Debian based systems while installing and maintaining packages:

Install a package:
`apt install nano`

Update your sources. apt has to have a "database" of software that it can install. At times you will modify the sources that apt can use to install software. After you update the apt sources, you need to update apt.
`apt update`

Upgrade all your installed software
 `apt upgrade`
 
 Check if software is installed
 `dpkg-query -l | grep nano`
 or
 `apt list --installed`
 For fun pipe that command to grep to search for nano and look at the error it spits out.
 
 Is a package containing the string `nano` available to be installed?
 `apt-cache search nano`
 
 Download a .deb
 `apt-get download nano`
 then ls and you will see the deb has been downloaded.
 
 And I already showed you how to fix broken package installs with `-f`.
 
 And you can remove software that you installed with apt with `apt-get remove nano` ( or ghc or whatever )
 
 Now, I mentioned before that apt needs to know where to download deb files that it can install. With out dpkg example above we downloaded a .deb with wget and then proceeded to install it. apt does the download automatically. It looks at the `/etc/apt/sources.list` file to know what software mirrors it can download debs from.
 
 I want to show you how to modify that file and install new software. To prepare this example, I just googled "packages only in sid" and got to this link: "https://packages.debian.org/sid/main/newpkg" and then I picked a random software package that is in sid, but is not in debian stable ( for us that is stretch, debian 9 ). I chose 'lazarus-2.0'. I have no idea what it is, its some sort of IDE for FreePascal. Pascal is a programming language, I imagine FreePascal is an implementation or something. Honestly I have no idea, I just chose a random package to install.
 
 ```
 $apt-get install lazarus-2.0
 Some sort of error message about package not found.
 ```
 
 So we 
 ```
 $ cat /etc/apt/sources.list
deb http://deb.debian.org/debian/ stretch main
deb-src http://deb.debian.org/debian/ stretch main
deb http://security.debian.org/ stretch/updates main
deb-src http://security.debian.org/ stretch/updates main
deb http://deb.debian.org/debian/ stretch-updates main
deb-src http://deb.debian.org/debian/ stretch-updates main
 ```
 
 You see all the repos are labeled as stretch. I'm going to add the sid mirror there so we can download some sid packages.
 Add the following to your /etc/apt/sources.list:
 
 ```
 # Unstable repo main, contrib and non-free branches, no security updates here
deb http://http.us.debian.org/debian unstable main non-free contrib
deb-src http://http.us.debian.org/debian unstable main non-free contrib
 ```

then `apt-cache search lazarus-2.0`. Nothing. We havent updated our software mirrors yet. Before we do, notice the options on these mirror lines. They say unstable - thats from sid. They also say main, that just means its the main software for that distribution release. They also say 'non-free' and 'contrib'. non-free means the software in this mirror is not 'free-as-in-freedom', though it is 'free-as-in-beer'. This software may contain binaries that you can't get the source code to. In the open source community people believe that you should be able to look at the source code of the software you use, just like you can take apart your car, to see how things work and to inspect for flaws.  As such, 'non-free' code is not endoresed by Debian, which is a freedom-oriented distribution. You can get the code by modifying your source list, but this software is not in line with Debian philosophy. Your call where your principles lay.

And it also says 'contrib'. This is free-as-in-freedom software that depends on non-free software. You can get it and use it, but it is similarly not endoresed by debian. Have a look in class at https://www.debian.org/doc/debian-policy/ch-archive#s-non-free, section 2.2 archive area for information about main vs non-free vs contrib

Actually, to install this lazarus package all you need is main, I just left the other ones there for you to look at and learn what they mean. If you want you can go into your sources.list and remove 'free' and 'contrib'  from the mirros we just added. `lazarus ` is in main, it is free software.

Now, to complete the exercise, `apt update` then `apt-cache search lazarus` - you see its available now! Then we `apt-get install lazarus-2.0` and it will install.

## aptitude
There is another tool called aptitude. I've never used it. It used to be very 'in'. It's another package management tool. Since I'm not familiar with it, I'm just not going to discuss it. If it turns out that it's important I'll include it in further revisions of this class. 

## rpm

On Redhat and the related distributions, like Fedora, Centos ( for others see https://upload.wikimedia.org/wikipedia/commons/a/a3/Redhat_family_tree_11-06.png ) you use the yum tool insteam of apt. And the package files are .rpms and not .debs.

The usage is similar to .deb and apt, but you have to learn the syntax that is particular to these tools. We will start another vm and this time change the boot disk to  Centos7. In this machine, for example, if you want to install pip, the python package manager, you can try to install it with `yum install python-pip`. Notice that on Debian you can `sudo apt-get install python3-pip`. If you try to `yum install python3-pip` you'll get an error message. This course id debian focused. RedHat flavored distributions have similar repo management methods ( Debian has the /etc/apt/sources.list file ) to Debian. Then the yum tool has all sorts of command line options just like apt-get and apt have. To see them you type 'yum -h'.

To be honest, I'm not preparing this part of the lecture because of my own lack of experience with Redhat. I used Centos 6 for 2 years a couple of years back, but I was working on a Hadoop / Spark stack and didn't do too much package installation after the initial cluster was configured. Maybe for future iterations of the class I'll spend a few hours writing some fun notes about the details of package management with yum.

For the next part of the lecture you can use either the debian instance or the red hat instance.

## from source
For this part of the lecture, we're going to focus on curl. From the manpage:

```
       curl is a tool to transfer data from or to a server, using one of
       the supported protocols (DICT, FILE,  FTP,  FTPS,  GOPHER,  HTTP,
       HTTPS,  IMAP,  IMAPS,  LDAP, LDAPS, POP3, POP3S, RTMP, RTSP, SCP,
       SFTP, SMB, SMBS, SMTP, SMTPS, TELNET and TFTP).
```

We're going to install the curl package on the debian instance because I know how to get the dependencies right, quick fast and in a hurry. You should wget the curl code from here:
https://github.com/curl/curl/releases

We're going to get version 7.64. On your system you can check the installed version with `curl -V`.

Get the .tar.gz package. Unpack it with `tar -xzvf *.tar`. Have a look around. You'll see a bunch of source code files, documentations, build scripts, etc. What you are looking at is the raw uncompiled code that becomes the curl package when properly built.

Make sure that a C compiler is installed along with the ssl library needed for https. ( discussion of https + openssl )

```
apt-get install build-essential
apt-get install libssl-dev
```

you can see full build instructions in curl-Version/docs/INSTALL.md

We will do the following:

```
./configure --with-ssl
make 
make install
```
After the make and make install we can test out curl with 

```
curl -V
curl https://www.google.com
```

We will see an error. Notice the discrepancy between curl and libcurl versions in the output of curl -V.  See th e"invalid option blah blah" error output of hitting google with curl. We can investigate the error farther. Before proceeding, I want to tell you that this is why we use package managers. Already you may be feeling worried, uneasy, and I felt the same way in preparing this lecture. I wasn't sure if I would be able to quickly sort out the root of the error of this install from source of a relatively common package. The package manager makes the install process faster and more painless. Also, we have now just built some files and dumped the compiled code into critical parts of our computer. If we have made a mistake, and overridden some important library or utility with some botched version we just built incorrectly, we may have a long painful journey ahead of us in fixing the issue. (Issues like this aren't toooo terribly bad if we've put all our sensitive media on a separate disk and can just wipe the boot disk and reinstall Linux!)

Anyway, we'll investigate now. 

```
which curl
/usr/local/bin/curl
```
notice this is different than before. The previous version of curl was in /usr/bin. Now we've installed in '/usr/local/bin', and if we check our PATH

```
echo $PATH
/usr/local/bin:/usr/bin:etcetera....
```
we see that the binary in /usr/local/bin has precedence. ( PATH precedence is the first match found!)

and if we check 
```
ldd /usr/local/bin/curl
```
we see that this version of curl is still trying to link against the libraries that /usr/bin/curl was linking against.
To verify, check out `ldd /usr/bin/curl`. That's why we saw in curl -V that curl was 7.64, but libcurl was 7.52. And if we check `/usr/bin/curl -V` we see that it is version 7.52, just like the libs. So there are a few ways to fix this issue. I'll just show you one so you can see that this issue can be fixed, but I'll leave you with the warning that installs from source can be tricky! They are sometimes necessary, sometimes fun, but often dangerous!

A solution:
1. When we run .configure, you can change the install location to be /usr/bin.

2. We're just goofing around, so we'll do it a different way!

---
Interlude

Do you know what a shared library / static library are ?? These is essential computer programmer knowledge. We are about to mess around with some .so files, which are shared objects. These are libaries that are to be shared amongst many running programs.  These are bits of code that any running program can link against to leverage the functionality of that bit of code. In windows these are dlls, they are dynamically linked libraries. 

The alternative to a dynamic library is a static one. A static library is some code that is compiled into the binary that uses it. Consider a video game  - video games need some code that gets the video game to draw pixels onto a screen. Every video game needs that. Option one is to write the function `draw_pixel()` and add it to every single program you compile.  So then the source code for red dead redemption, and the code for Sonic and the code for team fortress 2 all contain this function. This is a static library. Alternatively you write the function and compile it once. Then you provide a mechanism so that all your other games can use that compiled bit of code. You save alot of space on your machine! Now those 400Mb of pixel drawing code only takes up 400 Mb on your computer. If you rolled it into every game, every game would be 400Mb larger!

That's the good of dynamic libraries.

---

```
ls -l /usr/lib/x86_64-linux-gnu/libcurl*
```
You will notice that there are three results. Two of them have arrows next to them. These are called symlinks. So there is only one library in those results, and it is called `libcurl.so.4.4.0`. The other two are links that point to something else. So libcurl.so.3 points you to libcurl.so.4, which points you to libcurl.so.4.4.0, which is the source of our trouble. We need only replace libcurl.so.4.4.0 with the version of the library that works and we're good to go.

```
sudo cp /usr/local/lib/libcurl.so.4.5.0 /usr/lib/x86_64-linux-gnu/libcurl.so.4.4.0 
```

Now we will run curl -V again and we see that the problem is fixed. The version of libcurl and the version of curl match. ( draw the links on the board and just erase the lib.so.4.4.0, erase that and copy the other in its place.

Now try to hit google with curl. It will work.

```
curl https://www.google.com
```

Of course, this was an awful solution to the problem because there may be other packages that depend on the 7.52 version of libcurl, but now they have the 7.64 version, and this may cause those programs to crash! Better to let the package manager think about that stuff.


But that is in general the purpose of these links. Most executables are probably trying to use the links, so if we just change where the links point, or if we change the thing they are pointing to, we can solve our problem. There's much more to be said about this matter, and if you know alot about the links and shared libraries you  may be recoiling in horror at what I've just done. It's just an example to get things working and to get on with the lecture. If we ever run a class on "Linux System's programming" we'll talk more in depth about this matter there.

The bad of dynamic libraries is what we've just seen. Now we have changed on of the dynamic libraries on our system, so all the programs that were linked against libcurl used to have libcurl 7.52, but now they are receiving the 7.64 version and they might break! This is the purpose of those symlinks. The code points to a symlink and not the code itself so we can manipulate links and not code.

Some more info about curl:

curl informaion page
https://packages.debian.org/search?keywords=curl

curl dependency information is here. (Make sure to note the different architecture types).
https://packages.debian.org/stretch/curl

curl deb is here
https://packages.debian.org/stretch/amd64/curl/download
