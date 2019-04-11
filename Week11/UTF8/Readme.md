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

Look here after working on the example above:
https://www.fileformat.info/info/unicode/char/1f603/index.htm

Notice that after doing the above you can also do this:
echo -e "\U0001f603"
to achieve the same effect - this is the 8 digit representation of the unicode character. I'm on bash 4.3 with my computer properly configured with fonts to print this character. The computer has to know how to print the unicode character - even if bash understands it your terminal needs to have a notion of what graphic to dump on the screen.

bash also supports the 4 character unicode code points with a small u - for example, look a this:
echo -e '\u2211'
the summation operator.
https://www.fileformat.info/info/unicode/block/mathematical_operators/list.htm


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

## For the web programmers in the room
The &nbsp is all over the html Ive seen in the wild. What is this character? Is it ASCII or a unicode character? 

## Sed

## About programming languages

Are there any programming languages that allow you to use non-ascii characters for variable names? Most languages seem to use ascii characters, generally a-zA-Z, and maybe "-" and usually digits if they are not the first characters in the string. Why cant
we use the laughing emoji as a variable name? Is there any such programming language? If not can we simply modify awk to accept unicode variable identifiers? Is there any benefit to doing this? The APL language https://en.wikipedia.org/wiki/APL_(programming_language) supports a bunch of mathematical symbols. The R programming language offers one ascii based symbol "<-" for assignement ( instead of using '=' it is recommended to use the arrow as it better matches statisticians' work flow). What is the "<-" symbol and how to grep for it.

Look at comment here https://softwareengineering.stackexchange.com/questions/216641/languages-supporting-unicode-logic-operators about languages that support unicode. Allegedly Julia does - I never used julia though, would be fun to check it out with the Atom plugin they describe. Also notice the comment about hating people who put accented spanish language characters in comments becuase it made it impossible to handle code with some tools that would crash due to the tools only expecting ASCII. Indeed, ascii is easier to manage because a variable width type means you have to use logic when handling it. If you use ASCII chars you know every character is one byte wide. 

## There is more to the story. Beyond ASCII and utf8 there are other encodings.
I've worked with UTF16 a bit on windows. Look back at this chart https://www.fileformat.info/info/unicode/char/1f603/index.htm and youll see that the smiley face we already worked out the hex representation for in utf 8 ( f09f9883 ) is not the same as the uf16 hex representation (d83dde03). The prefixes we saw before ( 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX) do not hold true for utf16, the encoding is different. You might need to learn about it for your travels in computer science. Almost all of my work has been with ASCII and UTF8 text, but your experiences may be different.

## In the news, an aside
$99 cuda capable machine.
https://devblogs.nvidia.com/jetson-nano-ai-computing/?ncid=em-ded-ndcdcgdrnr-82651&mkt_tok=eyJpIjoiTTJKaU1EYzVaR1UxTm1WbCIsInQiOiIrN2FSanY5RkxcL2NIRXIyck11MzI3NkhVcUhVRFl0NjU1d0tWMVMza2wyaGNGNGVldllTQWtoaXFvamtRVnRDcFlRWjEzY0hRQW9XejVMaERcL1daOWl6SHdiRlVcL2ZINHU1bVp0OHhhM2Z4dWJDY1ZjaFZaVFhpWFZ1VWtTRzRGZyJ9
