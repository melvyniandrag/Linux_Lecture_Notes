# How to install software

To start, a bit of trivia. Debian releases are named after toy story characters! You can see your debian release name with 
`lsb_release` -a. We are using Debian 9 in the cloud, that codename is Stretch. Reference: https://unix.stackexchange.com/questions/222394/linux-debian-codenames . Debian is famous for moving slow, releases/updates are infrequent. The distribution undergoes extensive testing and very few new software packages are allowed into the distribution at a time. Other distributions releae updates very frequently with all kinds of new code. These distributions are less secure than debian, but oftentimes easier to use because whatever softwrae you need is there, available for the distro. 

There is a testing distribution that is pending release. Right now Debian Buster is the testing distribition, it will be released as version 10 some time in the future. The unstable distribution that is even less stable than the pending release is always called `Sid`. This is just a bit of cultural knowledge for you. I'm telling you this because it's good to know, and because we'll be reading some documentation today that refers to things like `Buster` and `Jessie` and `Sid` and I want you to know what you're looking at.

In particular, we are going to look at  `curl` today. Have a look at the `curl` page https://packages.debian.org/search?keywords=curl and you'll see the code names I've just mentioned to you.

## apt
99.99% of the software installs I've done have been like `apt-get install $SOFTWARE`. `apt` can do more than this however. `apt`, by the way, is the package manager on debian.

## yum

## deb
The package manage on Debian is dpkg, and it's a bit of a pain in the neck to use, this is the reason why apt exists. The problem is that dpkg doesn't install dependencies for you when installing software.
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
Haskell Hello world:
https://wiki.haskell.org/Haskell_in_5_steps


curl informaion page
https://packages.debian.org/search?keywords=curl

curl dependency information is here. (Make sure to note the different architecture types).
https://packages.debian.org/stretch/curl

curl deb is here
https://packages.debian.org/stretch/amd64/curl/download

## More about apt

sources.list

## rpm

## from source

This will be covered more in depth next, as we install curl from source.
