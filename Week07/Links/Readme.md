https://medium.com/@wendymayorgasegura/what-is-the-difference-between-a-hard-link-and-a-symbolic-link-8c0493041b62

major difference:

delete the target of a softlink makes the link useless.
delete the target of a hard link and the link is still good.

examples:
Make a hard link:
ln example hardlink

make a soft link
ln -s example softlink

after making a hard link, check the link and the target with ls -i. Both have the same inode

ater making a softlink, check the link and target with ls -i. Different inodes.

With the make the hardlink thing a script. run the link as executable. Then delete the original. Run again. This doesn't work
with softlinks.
