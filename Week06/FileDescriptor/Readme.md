# File Descriptors

We won't say too much about this. Linux uses file descriptors for i/o
with sockets, files, etc. ( Show example of the file descriptors listed
under /proc/$PID/fd when running some bluetooth code. )

We'll just look at how you get extra file descriptors ( besides the 
standard 0/1/2 ) when you open up a file for reading/writing.

Compile, run, and inspect file descriptors for the FileIO java program.
