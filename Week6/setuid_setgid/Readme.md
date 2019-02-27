# Setuid and Setgid

There are some special permissions that can be assigned to executables in Linux. You can trick your operating system into running a process as root, even though you are not root. The idea being, maybe you have a very trusted program that needs to do some root stuff. You are absolutely sure that the root stuff it does will not destroy your system, so you want to allow other users to do the root stuff even though they aren't root. <Flesh this out with some more discussion until it is clear>. 
  
A use case that I had was I wrote a very secure docker container and wanted anyone to be able to build and launch it, connected to a few system resources. I needed root permissions to make this happen, but I didn't want to drop into root all the time I wanted to do this safe thing, so I wrote a little program that would do some "rootly stuff", set the permissions and ownership of the file appropriately, and now I can run it as an unprivileged user.

If you call setuid(0) in your program, it changes you to the root user from the eyes of the operating system and lets you do rootly stuff.

## uid
In Linux, all users have a user id. You can get your user id from the command line by typing `id`. We haven't talked about this uid yet, and we certainly haven't used it, but it has been there all along. Today we will see what it is and we'll use it.

Try this:
```
$ id
[your id]
$ sudo su -
$ id
[you see user id is 0]
```
So now we know what the uid of the root user is. Check out this program:

```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
    int current_uid = getuid();
    printf("My UID is: %d. My GID is: %dn", current_uid, getgid());
    system("/usr/bin/id");
    if (setuid(0))
    {
        perror("setuid");
        return 1;
    }
    //I am now root!
    printf("My UID is: %d. My GID is: %dn", getuid(), getgid());
    system("/usr/bin/id");
    //Time to drop back to regular user privileges
    setuid(current_uid);
    printf("My UID is: %d. My GID is: %dn", getuid(), getgid());
    system("/usr/bin/id");
    return 0;
}
```

We see that with this program we make a few calls to getuid() and a few calls to setuid(). You don't have to worry too much about this program - if you don't know C it will maybe scare you a bit. That's why I've chosen this simple and illustrative program.  The main idea is that you see some source code here that calls these mysterious functions getuid() and setuid()! We can change our user id while the program is running to trick the computer into thinking you are root!

`getuid` returns the user id of the user running the program.




## A simple reference:
https://www.adampalmer.me/iodigitalsec/2009/10/03/linux-c-setuid-setgid-tutorial/
