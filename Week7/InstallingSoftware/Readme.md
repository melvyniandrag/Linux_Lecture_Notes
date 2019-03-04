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

curl informaion page
https://packages.debian.org/search?keywords=curl

curl dependency information is here. (Make sure to note the different architecture types).
https://packages.debian.org/stretch/curl

curl deb is here
https://packages.debian.org/stretch/amd64/curl/download


## rpm

## from source

This will be covered more in depth next, as we install curl from source.
