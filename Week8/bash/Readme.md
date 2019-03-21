# A bit more bash

In this part of the lecture we talk about a few more bash concepts. These might be useful
to you on your exam. The exam program is maybe the second legitimate programming exercise you've
had this semester, the first being when you had to find odd/even numbers. In your exam I've asked
you to write a script that takes in a text file ( ascii encoding ), count the letter frequencies in the file, 
and print out a simple table showing which are the most frequent and least frequent letters.
There are many ways to accomplish this task, and I'm going to give you a few more bash tools you
can use in case you can't figure it out with what you already know. Programming is a creative
art, let's see how clever you are.

## Associative Arrays


### What are they

Associative rays can be implemented in many ways. They have different names in different languages - 
they might be called a 'map' or a 'dictionary'. In C++ you have two options - an 'ordered_map', 
which is implemented as a hash map and a 'map' which uses binary search trees.  Python offers
a dictionary. Your prefered language probably has this data structure as well. 

But what is an associative array? It's a datastructure like an array, but instead of using 
numbers to index the array you use strings ( or other hashable/sortable datatypes ). Let's look at an example in 
pseudocode.

```
> array = [ 'john', 'jane' ]
> println( array[0] )
john
```

We make an array of two elements and print out the first one by its numeric index. We have
already seen how to make arrays in bash, and we've done a little bit of manipulation.

An associative array is similar, but the indices are strings ( usually ). In pseudocode, that would be like:

```
> sounds = {}
> sounds['dog'] = 'woof'
> sounds['cat'] = 'meow'
> println( sounds['dog'] )
woof
```

There are times when you would want this type of datastructure,  you may come across a problem 
in your career when you see this type of datastructure is useful. I've been able to do your exam problem 
using this datastructure, but I've also been able to do it without this structure. It's a good tool
to know about. I didn't know - to be honest - that it was available in bash until about a week ago when I was thinking
up the exam problems. I wanted to make sure that there would be a few easy approaches to solving the
exam problems, and I knew the algorithm would be easy with a map / associative array. So I looked into bash 
and saw that bash offers this datastructure.

I'll show you in bash how to use it in a second. But first let's look at the homework problem 
from last week. I had you implement a silly little hash that outputs three values. Let's make 
a simple associative array based around this hash function. If you remember ,the hash function outputs 0
for evens, 1 for odds and 2 for strings ( or soething like that ). So we can generate three numeric outputs 
based on inputs. Now what I'm going to tell you is a peek inside a datastructure - you 
need to take an actual algorithnms / datastructures class to learn more. But anyway, what the computer
does is allocate an empty array of size three.

```
array[3] = EMPTY;
```

then to populate it we call our hash function myHash(). When a user says 

array[11123] = 'dog'

we compute the hash function of 11123, which outputs 1. So in the background the computer 
says array[11123] = array[myHash(11123)] = array[1] = 'dog'. Similarly if we say array['cat'] = 'animal',
the computer runs array['cat'] = array[myHash('cat')] = array[2] = 'animal'. And similarly if we say
array[24] = 'this is an even number', the computer will run
array[24] = array[myHash(24)] = array[0] = 'this is an even number'

the same happens when we try to access the elements i our associative array - 

```
>println(array[24]) # computer checks the value in array[myHash(24)] and returns that.
'this is an even number'
```

this is roughly how hash based associative arrays work. Associative arrays can be based
on binary search trees and other data structures too, but we'll leave that to be discussed in
algorithms class.Anyway you might have spotted an issue. The issue has a name and it is 
'hash collisions'. In our program we don't usually want to specify the hash function used, and we don't want to 
worry about how much memory is allocated to the underlyig array beneath the associative array.
So we just say

```
assoc_arr = new AssociativeArray();
assoc_arr['cat'] = 'meow'
assoc_arr['dog'] = 'woof'
```

But what happens when we try to print out the value of assoc_arr['cat'] if we used the hash function above?
'cat' and 'dog' hash to the same value - 2, so we have a collision. The assoc_arr['dog'] assignment
overwrote the 'cat' one. 

In any event, these hash collisions don't usually happen in practive because the programming
language and library designers work very hard to design amazing hash functions that have extremely
low collision probabilities. So now you have a notion of how associative arrays work. 
To repeat - associative arrays are like regular arrays, but they aren't indexed by numeric index - 
they take keys that could be integers, strings, or other datatypes. Bash supports these.
Why is this important to you? One. This is a cool and ubiquitous datastructure. Two. You can use
this datastructure on your exam if you want. You are tasked with counting the occurences of certain characters 
in a text file and then printing out a neat little graphic with the frequencies counted.

One way to keep track of letter frequencies is to build an associative array:

freqs['a'] = X
freqs['b'] = Y
...
freqs['z'] = Z

then if you can figure out how to sort this thing maybe you could easily print ou the diagram indicated in the exam.
Before I show you the bash syntax for associative arrays I'm just going to tell you a bit more about bash itself.

### references
https://www.linuxjournal.com/content/bash-associative-arrays


## bash variables are untyped
Bash variables are untyped. Contrast this to a C program [ show a C program in class and 
show how variables are typed ]. There are many different typing schemes in different programming
languages. In any event, bash variables are untyped. You can do arithmetic on them if they contain 
only numbers. We've already talked about this so I'm going to omit examples. We saw how if and while and test behave differently on numbers vs strings. The interesting bit is that you can declare variables in bash to be of a certain type.

### references:
https://www.tldp.org/LDP/abs/html/untyped.html

## declare, typeset
declare and typeset are synonyms - I've only ever used 'declare', but according to the documentation I've linked below they are synonyms. I'm just going to talk about declare, and if you want to put in the leg work to verify that declare and typeset are synonyms, that's up to you. I'm from a C++ programming background, so I'm terrified to use anything I don't understand inside and out - C++ offers you a million ways to 'blow your leg off' when coding and it's made me deeply suspicious of programming languages. Without further ado...


You can declare the type of a variable. The effects of this vary depending on how you've declared it - in general it will restrict or modify the way a variable behaves.

### example 1 -r
```
declare -r var1=1
echo "var1 = $var1"   # var1 = 1
(( var1++ ))          # x.sh: line 4: var1: readonly variable
```


### example 2 -i
```
declare -i number
# The script will treat subsequent occurrences of "number" as an integer.       

number=3
echo "Number = $number"     # Number = 3

number=three
echo "Number = $number"     # Number = 0
# Tries to evaluate the string "three" as an integer.
```

### example 3 -A

this makes an associative array.

```
declare -A assoc_arr
assoc_arr['x']=1
assoc_arr['y']=2
echo ${assoc_arr[@]}
echo ${!assoc_arr[@]}
```

### references:
https://www.tldp.org/LDP/abs/html/declareref.html

## Sorting
Sorting algorithms are lots of fun and important to learn about. I told you some cool stuff about associative arrays, but 
sorting can't be talked about quickly. We only talked about associative arrays because they are 
simple in principle and easy to disciss. Anyway, we've seen at some point in this class the
`sort` utility. I'll just tell you about some command line options it has.

As we've already seen, Bash handles variable types in a way different than many other languages do. 
So sorting has some options to handle this. In general I'll just show you how to sort based on 
columns, how to sort based on strings vs numbers, how to change the column delimiters, and how to reverse sort.
The options we'll cover are `-k`, `-n`, `-g` and `-t`.

We will make a file

1 2
2 1

Then we will try to run sort in the following ways:

```
cat sortFile1.txt | sort  -k2
cat sortFile1.txt | sort  -k1
```

Notice that k changes the column we sort on


The lets make another file
11 2
2 1

Then run

```
cat sortFile2.txt | sort -k1
cat sortFile2.txt | sort -k2
```

Notice that something strange happens - the first column doesnt get sorted in descending order as the second one does. Why? Because bash is treating the numbers like strings, and not like integers! And, as a string 11 < 2. There are a few ways to look at why that is true. I'll give you some juicy information to help you understand better why that is soon. But for now, we can fix the sort by telling sort to treat the values it is sorting as numbers with the -n flag.

```
cat sortFile3.txt | sort -n -k1
cat sortFile3.txt | sort -n -k2
```

So now you know a bit about the k and n flags. How does k know what a column is? By default sort uses spaces and tabs as the delimiter. You can take the last file and, for line one, add a bunch of spaces and tabs. You will see that the same command works.

11                         2
2 1
 
We can chage the column delimiter if we want. You use the -t flag for that.Make a file like this

11:2
2:1

And run

```
cat sortFile4.txt | sort -n -t: -k1
```

and it will be sorted right. 

The -g flag allows you to sort by different types of numeric notation. Just so you know.

For example, try to sort this:

2.0:8.9
1.234:7.1
1.67:9.6

```
cat sortFile5.txt | sort -g -k1 -t:
```

There is more to be said about the -g option, but it's not relevant and we won't spend a few minutes looking at it and comparing it to -n. Choose the one you need. For integers, -n ought to suffice.


And -r sorts in reverse. Choose any of the above examples and experiment.

## How to make an associative array in bash

You need bash 4.0 or higher. Check `help -m declare`. You will see an option -A that allows you to make an associative array. Already showed you how. You can sort associative arrays if you want.

```
declare -A authors
authors=( [Pushkin]=10050 [Gogol]=23 [Dostoyevsky]=9999 [Tolstoy]=23 )

for k in "${!authors[@]}"
do
  echo $k ' - ' ${authors["$k"]}
done | sort -rn -k3
```

## let vs (( ))


### references:
https://wiki.bash-hackers.org/commands/builtin/let#examples

 Other references
https://www.artificialworlds.net/blog/2012/10/17/bash-associative-array-examples/https://stackoverflow.com/questions/1368563/how-can-i-use-the-unix-shell-to-count-the-number-of-times-a-letter-appears-in-a
https://stackoverflow.com/questions/8217049/bash-associative-array-sorting-by-value
https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash
https://stackoverflow.com/questions/6723426/looping-over-arrays-printing-both-index-and-value
