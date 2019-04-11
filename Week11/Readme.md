# Utf8

## Schedule
1. UTF8 discussion
  - look at the utf8 table in the pocogtfo article.
  - Look at some emojis and foreign language characters on the command line.
  - convert the hex for a cyrillic letter to a utf8 code point
  - convert the hex for an emoji to a utf8 code point
  - convert the utf8 code point for an arabic letter to hex.
  
  - convert a utf8 code point to octal.
  - convert a utf8 code point to octal.

Show how awk can be used for code points using hex and octal.
The take away from class today needs to be how to use sed to accomplish the homework task.


## Sed

Work through this tutorial: http://www.grymoire.com/Unix/Sed.html. we will read up to the section about  'sed in shell scripts', omitting the section about the cshell.

## UTF8

Recommended Reference: https://www.youtube.com/watch?v=n0GK-9f4dl8

See also 19:06 from https://www.alchemistowl.org/pocorgtfo/pocorgtfo19.pdf

## Useful bash tools

1. hexdump. Good reference: https://linoxide.com/linux-how-to/linux-hexdump-command-examples/ .
There are some hexdump results in this repository. As a class activity, have students decode the passages.

2. xxd. Great reference: https://www.linuxjournal.com/content/doing-reverse-hex-dump. As mentioned in the reference:
"If you work with the command line you've most likely used hexdump or od to dump binary files ...". I imagine you all have never done this, because you don't have much experience on the command line. hexdump and xxd are important tool I use almost everyday to inspect data files that may not always be ASCII encoded. xxd is like hexdump, but also allows you to undo the hexdump.



## Upcoming lectures
1. systemd vs initd, a look at linux init systems
2. Wrap up class with a few more bash/sed/awk tricks
3. Configure a git server ( this might be your final exam )
4. 

