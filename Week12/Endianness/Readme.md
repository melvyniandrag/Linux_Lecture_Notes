If there is time, let's look at endianness.
```
lscpu | grep ian
```
You'll see the byte order on your system.
What is  Little Endian vs Big Endian? This is a  crucial thing to know when dealing with your computer. It affects the way bytes
are stored. For a 4 byte unsigned integer, on little endian architectures the value is stored as 0x01 0x00 0x00 0x00, but on 
Big Endian the value is stored as  0x00 0x00 0x00 0x01. See, on little endian the smallest byte goes first, contrary to the way we
write numbers in English. In english the smallest digit goes to the right. On Intel CPUs the smallest byte goes to the left.

Check out the code I attached.
