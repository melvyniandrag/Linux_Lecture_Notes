# How to install software

To start, a bit of trivia. Debian releases are named after toy story characters! You can see your debian release name with 
`lsb_release` -a. We are using Debian 9 in the cloud, that codename is Stretch. Reference: https://unix.stackexchange.com/questions/222394/linux-debian-codenames . Debian is famous for moving slow, releases/updates are infrequent. The distribution undergoes extensive testing and very few new software packages are allowed into the distribution at a time. Other distributions releae updates very frequently with all kinds of new code. These distributions are less secure than debian, but oftentimes easier to use because whatever softwrae you need is there, available for the distro. 

There is a testing distribution that is pending release. Right now Debian Buster is the testing distribition, it will be released as version 10 some time in the future. The unstable distribution that is even less stable than the pending release is always called `Sid`. This is just a bit of cultural knowledge for you. I'm telling you this because it's good to know, and because we'll be reading some documentation today that refers to things like `Buster` and `Jessie` and `Sid` and I want you to know what you're looking at.

In particular, we are going to look at  `curl` today. Have a look at the `curl` page https://packages.debian.org/search?keywords=curl and you'll see the code names I've just mentioned to you.

## apt

## yum

## dpkg

## rpm

## from source

This will be covered more in depth next, as we install curl from source.
