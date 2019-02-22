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


# Looking at Partitions, Partitioning and Mounting

## Introduction

Lets look at the two drives we added, the one had a partition on it, the other one didn't. What does that mean??

lsblk -h shows us options for showing information about our drives. There's alot to take in. Let's focus on this command:


## gparted


If you weren't in class, here's a good reference to get you started

https://www.digitalocean.com/community/tutorials/how-to-partition-and-format-storage-devices-in-linux

You may notice that drive sda is 10G and the partition sda1 takes up the full 10G, whereas sda2 takes up only 4XX GB of the 500GB on the disk, and then sdc is a 500GB drive with no partition. There are some weird things happening here and I'm going to explain the basics to you.

We are going to format and add some space to our machine under /mnt, just to do it as an exercise.

```
sudo parted /dev/sdc mklabel gpt
sudo parted /dev/sdc mkpart primary ext4 0% 100%
lsblk
# now its there
sudo mkfs.ext4 /dev/sdc1
sudo mkdir -p /mnt/newdrive
sudo mount /dev/sdc1 /mnt/newdrive
lsblk
# now the partition is mounted
lsblk --output  NAME,FSTYPE,SIZE,MOUNTPOINT
```
You can also unmount the drive

```
#sudo umount mountpoint
sudo umount /mnt/newdrive
```

## Again step by step

```
sudo parted /dev/sdc mklabel gpt
```

We first label the disk. This layouts the structure of the disk. There are other names for the label - partition table and partition map are other names. The disk has some metadata about the partitions it contains and how they are structured, that's what this is for. You will mainly be interested in mbr/msdos or gpt partition tables. There's plenty to be said about mbr vs gpt partition tables. If you want to leave class knowing something, though maybe not understanding it fully - MBR is good for drives up to 2TB. Past that you need GPT. GPT is associated with UEFI whereas MBR is associated with BIOS. If you're confused, keep studying. In the meantime, just use gpt on Linux.

```
sudo parted /dev/sdc mkpart primary ext4 0% 100%
```

This command puts a partition on the labeled disk. The partition can be extended/logical or primary. For us we will make a primary partition. We also tell parted what file system type we are going to put in the partition. We will use ext4. There are many file system types, and you can read in depth about them if you're interested. ext4 is "the best file system type in Linux" in some senses, and not as good as file system types in other senses. It's up to you how much you want to know. Here's a reference to get you started:

https://opensource.com/article/17/5/introduction-ext4-filesystem
https://askubuntu.com/questions/44908/what-is-the-difference-between-ext3-ext4-from-a-generic-users-perspective

We also made the partition start at 0% and go all the way to the end of the drive.

```
sudo mkfs.ext4 /dev/sdc1
```

This puts the ext4 filesystem on the partition you created.

```
sudo mkdir -p /mnt/newdrive
```

create a mount point for your new disk. You can put it in mnt for now.

```
sudo mount /dev/sdc1 /mnt/newdrive
```

Now mount your disk. 

You can see it with 

```
lsblk
```
or also with

```
df
```

Now mount/unmount the drive a few times to check it out.

Add some stuff to the partition, unmount it, remount it. see stuff is still there.

unmount it and mount it somewhere else. 

see the stuff you created is still there under the mount point.

## restarting machine makes this go away

```
sudo reboot
#new terminal
lsblk #mounted disk not there anymore.
```

to make the disk permanently mounted, update /etc/fstab

add this line to the file:
```
#part     mnt point fstype ignore ignore ignore
/dev/sdc1 /mnt/data ext4 defaults 0 2
```

Here's a good reference. It explains what the last three parameters are. Not relevant to us now, but they are important. We won't discuss them because that would take us off track.

https://help.ubuntu.com/community/Fstab


TO SEE that it is now mounted even after reboot, reboot your machine!

```
sudo reboot
```

Log back in and see the partition is present.


## Move opt to separate partition

```
mkdir ~/opt_backup
cp -aR /opt/* ~/opt_backup  
sudo mount /dev/sdc1 /opt
lsblk
```

Note that /dev/sdc1 is not mounted at /opt. Notice that the contents of that partition are now visible under /opt.

Unmount the drive. Put some stuff in /opt. Remount the drive. Notice that the stuff you put in opt are hidden, but the drive stuff is there. 
The stuff is still there, if you unmount the drive you will see the files there - but when you mount the partition there those files are hidden by the stuff in the partition.

There may be ways to change this behavior, but that's not the way Linux works. 

# fdisk
There are many tools to use when partitioning disks. I like parted best - or gparted is best if you have a Desktop GUI! There is also fdisk, an older and oft used tool for partitioning.

Instructions on how to use it.
https://www.crucial.com.au/blog/2009/11/18/how-to-create-a-new-partition-on-a-linux-server/

Make sure your /dev/sdb1 is unmounted.

```
sudo fdisk /dev/sdb1
d ( delete partition )
n ( new partition )
follow instructions
p (view the part)
w (write the part)
```

Run
```
lsblk --output  NAME,FSTYPE,SIZE,MOUNTPOINT
```

To see there is no filesystem on the partition.

Then lets put a file system on the disk. If you want to try and mount it now, you'll see an error, the system expects a file system type there.

```
#If curious
sudo mount /dev/sdb1 /home/melvyniandrag/mntpoint
#error
```

So we'll put a file system on there.

```
mkfs.ext4 /dev/sdb1
mount the partition in a few places. Add files. Unmount, mount somewhere else, see the files are still there.
```

##Etc.
You may have noticed that with parted we specify a file system type when making the partition. That isn't essential, it's optional. See the documentation:

https://www.gnu.org/software/parted/manual/html_node/parted_19.html
