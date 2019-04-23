# Computer Security, Encryption, Cybersecurity, etc.

[ start loop test code in the background and don't mention what it is. Along the lines of "I'm just going to run this and don't you worry what it's doing."]

When you hide a key under the doormat to your house you are doing what is called "Security through obscurity". Another example of security through obscurity is using a combination lock to secure your bicycle. https://en.wikipedia.org/wiki/Security_through_obscurity The assumption is that a nefarious party won't know the secret that you are trying to hide. In the case of your key hidden in the flower pot out back, you assume a home invader won't find the key. In the case of your bike, you're assuming the thief won't guess your three digit code - there are usually 40 digits on the front so there are 40*40*40 = not that many combinations to guess from ! Security like this either assumes your attacker is unmotivated, severely pressed for time, or has some other trivial circumstance preventing intrusion.

## ROT13
Security by obscurity generally doesn't work in the digital world. If you try to do something simple like encode a message to your class during a lecture using a simple substitution, like mapping the letters in your least favorite student's name to the letter after it, you'll get something like:

** mjovy **

Given that someone had enough time to attempt decryption with commonly used encryption schemes, they would probably get this answer. Especially on a computer, the task is trivial! What I've just shown you is an example of a *cipher*, where every character is mapped to a different character. When I say the task of deciphering is trivial to a computer, it's because computers are incredibly fast! Check out the following code that runs through the numbers 1 to one million! 

```
#include <iostream>

int main()
{
  int total = 0;
  for ( int i = 0; i < million; ++i ){
    total++;
  }
  std::cout << total << std::endl;
}
```

Computers are kind of stupid, all they can do is manipulate bits - but they can manipulate bits ver, very fast! Ciphers don't stand a chance against a computer program that quickly tests combinations!

Nevertheless, ciphers, as primitive as they are, do have a place in the world. The rot13 cipher, for example, is commonly used to avoid bots. Some people [ need example ] who put their emails online will rot13 encode it so that spam bots don't see it's an email. More commonly I've seen people put "melvyniandrag [at] jee male DOT com", as this scheme is probably more resilient. 

Rot13 is "rotate by thirteen characters". [write alphabet on board and show how a -> n ]. So a maps to n, b maps to o, etc. You can use other rotation schemes too, like I showed you Rot1 at the beginning of class. Here's one way to do rot13 on the command line:

```
tr 'A-Za-z' 'N-ZA-Mn-za-m' <<< "The Quick Brown Fox Jumps Over The Lazy Dog"
```
Notice that there are three "<" in this command. This is an example of a "here-string". Don't worry too much about it, and if you want to know more I've put a link in the lecture notes. Anyway, you will see that T -> G, as T maps to G in the rot 13 scheme ( after z we wrap around back to a ). To decrypt rot13 is simple :

```
tr 'A-Za-z' 'N-ZA-Mn-za-m' <<< "The Quick Brown Fox Jumps Over The Lazy Dog" | tee rotated_text.txt | tr 'N-ZA-Mn-za-m' 'A-Za-z'
```

As an aside, this text "The quick brown fox jumps over the lazy dog" is a famous sentence used in schools for handwriting practice, as it features all the letters of the alphabet in english.

> Question: Are there other sentences like this used in handwriting class? I'm mainly interested in Spanish, Portuguese and Russian, but generally like learning about foreign languages. Do you have any samples of sentences like this in foreign languages?

> Question: How do ciphers handle UTF8 code points? How could you design a cipher to handle UTF8? One solution is to shift every utf point to the one after it. E.g. U+abcd -> U+abc(d+1).

Rot13 reference: https://en.wikipedia.org/wiki/ROT13 
Here string reference: https://unix.stackexchange.com/questions/80362/what-does-mean

## Another cool trick for cybersecurity

Before moving on I'll give one more example of why ciphers are bad! A sophisticated algorithm can use frequency analysis to decrypt a message that used a cipher. We already looked in class at how certain letters in english have been statistically shown to appear with a certain frequency. Of course, statistical analysis only holds for large bodies of text! The quick fox sentence has frequency ~1 for every letter. But, if you take the collected works of shakespeare and make a histogram of letter frequency and compare that to the histogram of letter frequencies in all the NYTimes articles written this year, you'll approximately see this [ does anyone have nice figure to give me? ] https://en.wikipedia.org/wiki/Frequency_analysis with the letter e appearing most, followed by the letter XX followed by YY , etc. Using this technique, you could look at the bytes in a file and map the most common one to e, the second most common one to XX, etc.

> Idea for a fun hacking project - make executables that can be deciphered to be good prose following a suitable cipher/decipher scheme. 
> Idea for pygotham - do the above with Python scripts. Encode python scripts as poems using a suitable cipher. Distribute code as prose.

> Idea for class - design a lab that can be performed in ten minutes to do frequency analysis deciphering.

In any event, we've seen that ciphers are not so good for protecting sensitive data. Security through obscurity is generally not good. If anyone knows that you've simply rotated text by thirteen characters, they can decode your message. And, in some cases, they can decode even without knowing the scheme through a more subtle method like frequency analysis.

## History of PGP, GPG, OpenPGP, GnuPG.
To learn a bit about pgp / gpg there is a great reference by a guy names "Michael Lucas" and the book is called "PGP & GPG email for the practical paranoid". In this ~200 page book he goes through the history of these tools and how to use them. I'm maybe going to save you
$25 dollars and tell you lots about what's in the book. https://nostarch.com/pgp.htm It's a good enough refernce though, if you want to pick it up and have it on your shelf. Indeed, I'm going to tell you alot tonight, and you'll learn quite a bit, but reading this book on a lazy saturday would be a great way to solidify your knowledge.

[ TODO Fill this in with a few cool facts from the book ]

## Using GPG

### Why should you know about GPG keys? 
GPG keys are used for encrypting/decrypting data and verifying the authorship/provenance of email/data. These keys are industry standards and as we mentioned, they are backed by some serious mathematics.

GPG keys are used in industry, especially in the opensource community. If you uploaded an ssh key to github for streamlining your git pushes, you may have noticed there was also an option for uploading your public gpg key. They explain here: https://help.github.com/en/articles/adding-a-new-gpg-key-to-your-github-account how to do it as well as which algorithms they support.
Furthermore, Linux kernel developers use GPG keys when making changes to the kernel. For example, you can see that Linus Torvalds has one of his keys public available on a "keyserver" here: https://pgp.cs.uu.nl/stats/17762c4676e21cbb.html . 

My gpg key can be found here:
https://keyserver.ubuntu.com/

If you search for 0xA8320558FF022DF5B6885B18FDF81434D7494435

There are various numbers on these pages and talk about signatures - we'll talk about what that stuff means now. 

### key vs subkey
Generally you should use the sub key for encryption/signing and not the public key. Read more in the man pages, or the summarized details in this link: https://superuser.com/questions/1371088/what-do-ssb-and-sec-mean-in-gpgs-output

## generating keys
Enough talk, let's do something now!! To generate a key you use the gpg command line tool. The tool will generate a public key and a private key - you must guard your private key with your life!! This key can be used for decrypting messages encrypted with your public key - but it can also be used to forge your signature! And the tech world generally views this signature as being an indisputable means of demonstrating that YOU are the author / creator of somethign signed with that key. So if some message on the internet shows up signed with your key, and this is an unsavory kind of message, you could be in deep trouble or at best have to jump through hoops to demonstrate that your machine was hacked and your private key taken.

```
 gpg --full-generate-key
```

will generate keys. It will ask you for some information. You should add a password to your key for extra security. Take time now to write your password somewhere safe and store it away. Don't ever lose this password, or you won't be able to recover your key later. This could be a security problem. At the very least you'll have a dead key floating out in the wild confusing everyone.

You need to put your name and a bit of identifying information about yourself on the key, so in case someone finds two keys with the name "Melvyn  Ian DRag" on them, they'll know the one they want is the one from the embedded Linux developer who loves dogs and not from the React Native expert who loves cats. Just a few identifying words!

You're going to want to choose RSA/RSA if it is available and use 4096 bits for your key length! The more bits the better, and I think 4096 is the upper bound now, but I'm not sure.

## encrypt and decrypt

## digital sign and verify

## import other people's keys

## keyserver
I already told you where my key is, it's on the ubuntu keyserver. I've also uploaded my key to the mit keyserver, but the server is hit or miss if it's online. I always get a proxy error when using that server, and I've seen this issue documented at least on Reddit https://www.reddit.com/r/pgp/comments/aorc6a/mit_lookup_fails_with_502_and_503/ This would be a big pain if you had written some script that was making curl requests to the mit server and the server was down.

 ## quantum computers and microsoft visit


### gpg vs gpg2
I've always used gpg. There is also gpg2. Admittedly I should look into gpg2 and see what it's all about. There is a description of the differences here: https://superuser.com/questions/655246/are-gnupg-1-and-gnupg-2-compatible-with-each-other but I haven't had time to look into the differences, read the docs, and make a choice if gpg2 is right for me or not. If you're interested, you could look into it. As always, there are things I don't know. If you have the time to investigate and report back with information that would be great!

## Hash vulnerabilities
We've talked about hashes several times in this class, and used md5sum and maybe discussed sha hashes, sha1 and sha256. I'd be remiss to not mention a hash vulnerability found in git a few years ago. What's the purpose of a hash? As we've seen, when you download software  - here's an example, the dragonfly bsd Operating System  https://www.dragonflybsd.org/download/ [ open link and show class ] - the software provider gives you some md5sum values to verify that the data is good. The idea is that you feed data into a hash algorithm and out comes some uniquely identifying information. But md5sum is only 128 bits! That means that there are only 2^128 different outputs possible! 

1. [128 zeros]
2. 1 [127 zeros]
3. 11 [126 zeros]
4. 01 [126 zeros ] 
5. etc.

But there is more than 2^128 possible inputs to the algorithm. So there WILL be a hash collision. FOrtunately, the collision is so unlikely that we accept the risk. A genious hacker would provide an operating system image that contained malware, but generated the same hash, and thus you would 

> Idea: Get source code for an operating system and write a virus. Then put that virus in various points of the code one by one. ( probably you want to write some software to automate this ). Compile the operating system and check the hash each time. When you get an image with the same hash, that contains your evil code, then you find a way to distribute the code in place of the original image and infect people. This would be a great little research project for someone here. As a baseline, how long does it take to loop from 1 to 2**128? 

> Question about the last idea - whats an integer datatype that contains 128 bits? 128bits = 16 bytes, so there is none. 

SEE_LOOP_TEST_CODE_NOW

HAve a look at this website too: https://shattered.io/

Show in class how two pdfs generate the same sha1 hash.

```
wget [ link to pdf1 ]
wget [ link to pdf2 ]
sha1sum pdf1.pdf
sha1sum pdf2.pdf
```

make sure to show that the pdfs are differnt in class, yet generate the same sum. Scroll through the website and show how many systems are affected by this! git, gpg, etc.

SHAttered reference: https://github.blog/2017-03-20-sha-1-collision-detection-on-github-com/

## References
Michael W. Lucas PGP&GPG - email for the practical paranoid
Cool article about tr - https://www.linuxjournal.com/article/2563
