# UTF 8

## Introduction

We will look at these emojis and how to handle them in Linux.

```
 echo -e "\xF0\x9F\x98\x81"
 echo -e "\xF0\x9F\x98\x82"
 echo -e "\xF0\x9F\x98\x83"
 echo -e "\xF0\x9F\x98\x84"
 echo -e "\xF0\x9F\x98\x85"
 echo -e "\xF0\x9F\x98\x86"
 echo -e "\xF0\x9F\x98\x87"
```

https://apps.timwhitlock.info/emoji/tables/unicode
https://en.wikipedia.org/wiki/UTF-8


## AWK

Awk supports utf8. Clone and run the original AWK, to get away from the gawk that is installed on your system.
(gawk has many useful extensions and you can just use gawk when you're out in the real world. This is just so you have another experience
of installing from source.)
https://github.com/onetrueawk/awk

I got interested in this because on page 31 of "The Awk programming language" they list the escape sequences available available, but hex doesnt come up. HEX represents bytes very nicely but I've not seen octal much in the wild - except we use a sort of octal notation 
for setting permissions. What is the appeal of octal notation to UNIX? each octal character represents 3 bits! bute we are used to ultiples of 2 and better yet multiples of 8.


``` 
echo -e "\xF0\x9F\x98\x87" >> angel.txt
echo "angel" >> angel.txt
```

Find repeated occurences of the angel emoji. 3 or more times - maybe you are pouring through you text message backups, you know your partner
always puts the crying emoji three times or more, so you want to find that. We'll just use the angel for now.

```
awk '/(\xF0\x9F\x98\x87){3,}/' ../angel.txt 
```

The () groups the characters together.
