# Swap Space
## Introduction
What is swap space? Your computer has RAM, Random access memory, where programs are loaded in and run from. This is volatile memory, as soon as you power off your machine everything in RAM is gone. This is different from non volatile memory, like a HDD or SDD, where files are permanently stored - things like your pictures, etc. We've seen in this class how to add more non volatile memory to your system, now we're going to ask the question - "what happens if you run out of RAM??" What if you want to have 10000 browser tabs open and not just 5, but your measly 8GB RAM stick in your laptop won't handle that kind of abuse? What if you want to run chrome, pycharm, vscode, inkscape, blender, steam, and a few other things at one time?? You can add more memory as swap space!

Swap space is some space on disk - on your HDD or SDD or USB or whatever that the OS uses to store data from RAM when  there is no more space! Collectively you refer to the swap space + the ram space on your system as the virtual memory.

## Overloading the memory on your system
We're going to use a stress testing utility to fill up the memory on the system. I could also have written a little program to fill memory, but this tool exists so we'll just use it. `apt-get install stress`.
Run tmux, split the pane. Run this 
```
stress --vm-bytes $(awk '/MemAvailable/{printf "%d\n", $2 * 0.9;}' < /proc/meminfo)k --vm-keep -m 1
```
in one pane and run `top` in the other. Watch how the memory is filled up.

## Lets add some swap space.
Is there any swap space yet?
```
sudo swapon --show
# no
free -h
# only ram is shown
```
Shouldnt be. By default you don't get any in your debian 9 google cloud vm.
```
sudo fallocate -l 1G /swapfile
```
Install fallocate if it isn't installed.

This just allocates 1GB for a file called "swapfile" located at "/". Then change permissions and configure it as swap.

```
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
sudo swapon --show 
# you will see that you have swap space now
free -h
# you will see you have swap space
```

You can play with this a few times to see for yourself how easy it is to add / remove swapspace.

```
sudo swapoff /swapfile
free-h
sudo swapon /swapfile
free -h
# do this a few times to develop muscle memory
```

## Playing around with swap space a bit
Notice that 
```
cat /proc/meminfo | grep MemAvailable
```
reports available RAM, and not swapspace. Lets try and allocate more memory than fits in RAM, by trying to put more than "MemAvailable" bytes into memory. We'll get the MemAvailable from /proc/meminfo and then multiply it by 1.1, and then try to stress our system by allocating that much memory. Then we'll look at top and see that some swap space was used.

Run two vertical tmux panes, in the left put `top` in the right, run this command. Notice that swap space is used.

```
stress --vm-bytes $(awk '/MemAvailable/{printf "%d\n", $2 * 1.1;}' < /proc/meminfo)k --vm-keep -m 1
```
Try to turn swap off and notice that the OS yells at you because it can't allocate the memory to bring the stuff out of swap back to RAM.
Then kill the stress test with CTRL C. Look at top. Notice that alot of stuff has stayed in swap space. That's an operating system thing. It could have been programmed to detect when there is space in RAM and always bring the swap stuff back to ram when possible, but it doesnt. You can force it to now by turning swap off. Maybe the OS does eventually pull it back to RAM I don't know. Maybe it waits an hour, or maybe there's another trigger, you'd have to look at the guts of the code to know for sure.

## Making the swap space permanent between reboot
You have to edit `/etc/fstab` just like with adding disks / partitions.

```
/swapfile swap swap defaults 0 0
```

## Swap space can be on it's own partition too
Add a disk to your machine.
```
parted /dev/sdX
mklabel gpt
mkpart primary linux-swap 0% 100%
print
quit
sudo mkswap /dev/sdXN
sudo swapon /dev/sdXN
```
Then play with the swap space as we did with the swap file, you can update fstab too.

## References
Follow these excellent online tutorials.:
1. https://linuxize.com/post/how-to-add-swap-space-on-debian-9/
2. https://opensource.com/article/18/9/swap-space-linux-systems
