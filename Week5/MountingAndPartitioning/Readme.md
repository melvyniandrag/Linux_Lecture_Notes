# An aside - A beautiful Thinkpad + Linux setup seen on Reddit
https://www.reddit.com/r/thinkpad/comments/arb27u/between_humanities_and_technologies/

Here's a person running Linux, compiling KDE and firefox while working on an english paper and studying cyrrilic.

# Drives, Partitions, Mounting, and Partitioning.
The idea of this part of the lecture is that sometimes you want to add storage space to your machine. You might have a 250GB SDD and you just bought a 1TB drive and you want to add it to your machine so you can download more movies, save more pictures, store more code, whatever.

## Look at what storage space you already have.

```
$lsblk
sda      disk
--sda1   part
```

sda is a physical drive on your computer, like a harddrive connected to the machine. sda1 is a partition of the drive, it's a chunk of memory you 
formatted in a particular way to become useable by your machine.

## Now we will add another drive

Read this: https://cloud.google.com/compute/docs/disks/add-persistent-disk
On your vm instance page click the instance name
click edit
click add item
click to add disk 1, by default 500GB disk
click save

now do this again
```
$lsblk
you have a drive called sdb now!
```

google cloud gave you a partition too. Note that this is different from the normal experience, there ought not be a partition there. We could have tweaked the partitioning too before adding it. Let's see that in action. Now we'll add an unpartitioned disk.

click add item as before, but this time in the drop down click "create disk" and create it, then save it 

now when you 

```
$lsblk
# theres an unpartitioned disk called sdc ( or something else! )
```

Windows normally gives your drives names like 'C:/', 'D:', 'E:', right? I'm not a Windows expert but I know that this is what it looks like on a Windows computer.





add a drive with google cloud

partition it with parted

mount the partitions

About  different partition types

About different filesystem types ext3, ext4, etc.

add another drive with google cloud

partition with fdisk

mount it
