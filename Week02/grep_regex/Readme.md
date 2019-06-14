# Pattern Matching, Regular Expressions, Grep

## Pattern matching in bash 
No we get into pattern matching in linux. A common way to match patterns in Linux is to 
use * when using bash. Lets make a directory called dir, and put a bunch of files in it. 
Lets name them:

```
$ mkdir dir
$ cd dir
$ touch cow coffee core care cape apple 
$ ls
$ ls c?re
$ ls c*
$ ls ca?e
$ ls ca[rb]e
$ ls ca[rp]e
```

You can use these wild cards in the terminal. So, for example, if you want to get the number of lines in all of the files in your current directory you could

```
cat * | wc -l
```

## Grep 

Now lets look at some more advanced pattern matching used in Linux via the grep command. 
Grep stands for Global regular expression print, it uses regular expressions to search for strings.
Now, grep is immensely useful, as we already saw last week. Last week we typed

```
history | grep wget
```

to look through our messy bash history to find exactly the command of interest to us, to see what files we downloaded in the past and to potentially download them again.

But there is an old Linux saying about regular expressions. "You have to solve a problem and you decide to use a regular expression. Now you have two problems."

https://opensourceforu.com/2012/06/beginners-guide-gnu-grep-basics/

A poem I like:
https://www.cc.gatech.edu/~spencer/poems/woods.txt

You can wget the poem

We are going to cover a bunch of grep options to pick apart this poem.

1. -i -> grep -i HARNESS woods.txt
2. -w -> grep -w arness; grep -wi Harness 
3. -v -> grep -v arness
4. -r -> mkdir -p a/b; mv woods.txt a/b; grep -r arness *
5. -n -> grep -rn arness *
6. grep can match lines before, after, and both. grep -A1 arness woods.txt; grep -B1 arness woods.txt; grep -C3 arness woods.txt
7. -l -> grep -l arness *
    > remember if we see any irrelevant error messages from grep, we can redirect them to the ether.
    ```
     grep -l arness * 2> /dev/null
    ```

    e.g.
    ```
    $mkdir dir
    $grep -l arness *
    grep: dir: Is a directory
    woods.txt
    ```
    
    BUT
    
    ```
    $grep -l arness * 2>/dev/null
    lecture.txt
    woods.txt
    ```

## Grep and Regexes!

Ah, but we have yet to get to regular expressions!

Regular expressions are for pattern matching.

https://www.gnu.org/software/grep/manual/html_node/Basic-vs-Extended.html

> In basic regular expressions the meta-characters ‘?’, ‘+’, ‘{’, ‘|’, ‘(’, and ‘)’ lose their special meaning; instead use the backslashed versions ‘\?’, ‘\+’, ‘\{’, ‘\|’, ‘\(’, and ‘\)’.

The period (.) matches any single character.
? means that the preceding item is optional, and if found, will be matched at the most, once.
* means that the preceding item will be matched zero or more times.
+ means the preceding item will be matched one or more times.
{n} means the preceding item is matched exactly n times, while {n,} means the item is matched n or more times. {n,m} means that the preceding item is matched at least n times, but not more than m times. {,m} means that the preceding item is matched, at the most, m times.

That's it! So, given the file a.txt ( see this directory )
We can do the following
```
$ grep "a" a.txt # Find lines with an a
$ grep "a\?" a.txt # find lines with an optional a.
$ grep "a?" a.txt # find lines containing a?
$ grep "a+" a.txt # find lines with 1 or more "a"s
$ grep "a$" a.txt # find lines that end with a
$ grep "+" a.txt # find lines with a +
$ grep "[0-9]$" a.txt # find lines that end with a number
$ grep "^[a-zA-Z]$" a.txt # find lines with one letter.
```

Some more syntax:
1. ^ (Caret)   =   match expression at the start of a line, as in ^A.
2. $ (Question)    =   match expression at the end of a line, as in A$.
3. \ (Back Slash)  =   turn off the special meaning of the next character, as in \^.
4. [ ] (Brackets)  =   match any one of the enclosed characters, as in [aeiou]. Use Hyphen "-" for a range, as in [0-9].
5. [^ ]    =   match any one character except those enclosed in [ ], as in [^0-9].
6. . (Period)  =   match a single character of any value, except end of line.
7. * (Asterisk)    =   match zero or more of the preceding character or expression.
8. \{x,y\} =   match x to y occurrences of the preceding.
9. \{x\}   =   match exactly x occurrences of the preceding.
10. \{x,\}  =   match x or more occurrences of the preceding.
