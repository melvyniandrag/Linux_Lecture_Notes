# Introduction
Bash is a relatively simple language if you compare it to something like Java. Nevertheless
the standard bash intro "Advanced bash scripting guide" available on tldp is nearly 1000 pages long!
So we are learning it piece by piece, and when you have a free week or so to read through the 
whole book you will be well prepared to skim the vast majority of it.

Some of the things I'm going to show you now may seem stupid or useless! But rest assured that what I'm telling you is important to your career as a computer programmer. There is a datastructure in python called a dictionary, it's more generally known as a map in computer science jargon. When I was reading my first python book about a decade ago I saw this data structure and thought it was silly and couldn't fathom why you would use this dumb thing. Fast forward ten years and I use dictionaries almost every day and can talk to you in depth about the lowlevel details of how they work, why they work, when they should be used, and when they shouldnt, etc.. So don't brush me off. Even if you don't understand all I say, I guess I hope you appreciate me planting the seed in your head about these important ideas.

# Arrays
This article starts out by saying:
"the intent of this article is to avoid having to RTFM", it's a great read!
https://medium.com/@robaboukhalil/the-weird-wondrous-world-of-bash-arrays-a86e5adf2c69

What's an array? It's a container of values. There's a bunch of uses for this! It's a list of values!
There are many data structures you can use for the values you are manipulating in your program, an array is just one container for holding them. 
You know there are priority queues, hash maps, a whole bunch of binary trees, etc., etc., to learn about these you need to take an algorithms class, or read an algorithms book.

An array is something like 

students=["omar", "Elizabeth", "Mackenzie" . . . ]

All languages that I know use arrays. Maybe there is a language out there that doesn't support arrays, but I don't know of it yet.

The array syntax in bash is 

```
arr=(1 2 3 4)
```

you can put strings and numbers in there like

```
arr=(1 2 3 "hello")
```

In bash to see variable contents you use the `$`. For example, if you say

```
a=1
echo $a
```

You can also wrap the variable with curly braces like this

```
b=1
echo ${b}
```

A time when you would use this curly brace syntax is to add extra characters to the output of a variable. For example:

```
z="cat"
echo $z
echo $zs
#error
echo ${z}s
```

Without the curly brace in this situation, bash thinks the variable is called "zs"

Bash variables do require the curly braces, however. I'll repeat now that I don't love the bash syntax, but bash is super useful, and it's everywhere, so we all have to know about it. Kind of like javascript.

```
arr=(1 2 3)
echo ${arr[0]}
# prints 1
echo ${arr[1]}
# 2
echo ${arr[2]}
# 3
```

If you omit the curly brace, like this:

```
echo $a[0]
# 1[0]
```

You see bash treats the "[0]" as a string. We won't go into the low level explanation of why this happens, but it does and that's just the way bash works. So you need the curly brace. Also, notice you won't get 'out-of-bounds' exceptions or crashes due to accessing elements that are outside the bounds of the array.

```
arr=(1 2)
echo ${arr[5]}
# nothing
```

it is what it is. Notice that bash uses zero indexed arrays. For all the yuckiness of bash array syntax, at least it uses zero indexing. And it's not that yucky either, is it? Just remember to use the curly braces!

How to dump the array and see the contents? This is another important thing you might want to do!

```
arr=(1 2 3)
echo ${arr[@]}
```

So the ampersand is used for dumping all the array contents.

Now let's get really funky for a second - bash array elements don't need to be sequentially indexed!!

Look at this example:

```
array[0]=10
array[4]=4
echo ${array[@]}
# 10 4

echo ${array[1]}
#nothing
```

Depending on your familiarity with other languages - but for this you can probably just use your intuition - this is really weird! Bash arrays are zero indexed. So you would expect the array to start with element 0, then there's element 1, then 2, etc.. But not with bash. You can have an array containing elements 0, then 4. Or you can make an array like this:

```
array2[10]=1
array2[12]=1
array2[100]=2
echo ${array2[@]}
```

We'll put arrays on the back burner for a second while we look into another topic.

# for loops

For loops are a common construct in many programming languages! C, Java, Python, Ruby, Javascript etc. all use this construct, so you've probably seen it before. Bash has it too.

A common use case of the for loop is when you want to loop over something a predetermined number of times. You'll say "for iteration = 1 to 100 do a thing. In bash to write this you say:

```
for i in $(seq 1 10)
do
    echo $i
done
```

type that a few times to make sure you understand it. ( seq is another command line tool to generate a sequence of numbers )

You also might want to loop over an array:


```
array=(1 2 3)
for i in ${array[@]}
do
echo $i
done
```

You might want to loop over an array by index, too! Now if you don't know why you would want to do this yet, don't worry about it, I'm going to show you the syntax anyway, and maybe you'll thank me sometie 10 years from now. Think about what I said about myself and python dictionaries.

Look at our previous array

```
array=(1 2 3)
for i in ${!array[@]}
do
echo $i
done
```

The exclamation point tells the loop to print out the array index instead of the array value. Notice that this prints out 0 1 2 - these are the indices of the array, because bash is zero indexed.

But, remember that bash arrays are strange and don't require sequential indexing.

```
arr[10]=1
arr[15]=2
for i in ${!arr[@]}
do
echo $i
done
# 10 15
```

# Populating arrays

Just a quick note about populating arrays

```
arr[1]=10
arr[20]=11
empty=()

for i in ${!arr[@]}
do
empty+=${arr[$i]}
done
#10 11
```

# while loops

There are also while loops in bash. Many programming languages support while loops, the same thing I said about for loops. A while loop is a loop that will run forever until a specified condition is met. 

while ( alive ) {
    eat
    sleep
    etc.
}


```
i=0
while [ $i -lt 3 ]
do
echo $i
i=$[$i+1]
done
# 0 1 2
```
I increment the variable i in this loop, but this isn't of too much interest to us at this moment. In the notes I have a link that explains the multitude of ways to increment a variable in bash. It's not worth it to us right now to spend a half hour discussing the ins and outs, pros and cons, etc. The important message here is that bash, like many other languages supports a loop called a while loop.

https://askubuntu.com/questions/385528/how-to-increment-a-variable-in-bash

http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_09_02.html

# alias

You use the alias command to change the names of system commands, implement system commands, etc. 

For example

```
touch filea
mv filea fileb
move fileb filec
# error
alias move=mv
move fileb filec
# now fileb is called filec
```

# .bashrc, /etc/profile.rc

There are many bash profile configuration files on your machine we need to mention now.

These files save custom system configurations. There are several of these files on you system, and the availability of these files may vary from system to system. We'll focus on the .bashrc file, which will work for 99% of your usage needs.

If you change a user's bashrc file, you'll be able to change the system configuration for that user. We can alias "mv" to "move" so that it persists every time we log on to our system.

Open a new subshell after aliasing move as you did above and try it again. Notice that the alias hasn't persisted to the new subshell - you can't use the alias, the system doesnt know about it.

```
alias move=mv
touch a
move a b
# works
bash
move b a
# error
```

```
# append 'alias move=mv' to the end of the bashrc file.
```

another vim tip is that you can go to the bottom of a file with 
shift+g. top is gg.

The rm command is a particularly dangerous command on your system, as we have discussed before. Whereas windows has a "trash can" when you delete a file, Linux does not. When you rm a file, it is gone forever - there are some hail mary ways to possibly, maybe, pleasepleaseplease save your rm-ed files, but generally speaking, if you rm a file it is gone for forever. Your homework deals with using your bashrc and an alias to make rm safer.


# back to arrays

Another useful reference:
https://www.tldp.org/LDP/abs/html/arrays.html
In general, the whole 'abs' - 'advanced bash scripting' guide is a great read!

I've maybe used a BASH array twice in my career, but that's probably because of my career path. I know the arrays are out there, and you shoulld know they are out there too.

# [ ] vs [[ ]] vs test

There are at least three ways to write ifs to check for conditions in bash.

You can write 

```
if [ 1 -eq 1 ]
then 
    echo "true"
else
    echo "false"
fi
```

You can also write

```
if test 1 -eq 1
then 
    echo "true"
else
    echo "false"
fi
```

The previous two are standard sh commands. The [[ ]] construct is a bash extension. It permits you to do more than the [] and test constructs allow, but it's not portable. 

https://www.tldp.org/LDP/abs/html/testconstructs.html

https://wiki.bash-hackers.org/commands/classictest



