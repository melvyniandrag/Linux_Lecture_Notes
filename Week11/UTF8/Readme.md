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

## To do next

Look at the above links.

Then work out the examples from the "code to run file I made there. have students work out another example, an arabic letter or something.


## Next next
What is the "<-" symbol - probably search for the utf8 code plane that contains mathematical operators. Lets sort out what the hex + octal values are for it, use awk and sed to search for it, and then use hexdump and xxd to verify the hex and octal representations of this symbol. It may be on this page:
https://en.wikipedia.org/wiki/Mathematical_operators_and_symbols_in_Unicode#Mathematical_Operators_block

If not, it should be called the assignment operator. Here are some arrows, we could use this:
https://unicode-table.com/en/sets/arrows-symbols/


After writing files using unicode characters we must use  hexdump and xxd to look at it.

## next next next
https://en.wikipedia.org/wiki/Mathematical_operators_and_symbols_in_Unicode#Mathematical_Operators_block
Look in this page for the mathemaicla letters block. Can you echo your name as a non-ascii string?

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

## Sed

## About programming languages

Are there any programming languages that allow you to use non-ascii characters for variable names? Most languages seem to use ascii characters, generally a-zA-Z, and maybe "-" and usually digits if they are not the first characters in the string. Why cant
we use the laughing emoji as a variable name? Is there any such programming language? If not can we simply modify awk to accept unicode variable identifiers? Is there any benefit to doing this? The APL language https://en.wikipedia.org/wiki/APL_(programming_language) supports a bunch of mathematical symbols. The R programming language offers one ascii based symbol "<-" for assignement ( instead of using '=' it is recommended to use the arrow as it better matches statisticians' work flow). What is the "<-" symbol and how to grep for it.
