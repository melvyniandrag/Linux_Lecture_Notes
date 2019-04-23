# Computer Security, Encryption, Cybersecurity, etc.

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
## Using GPG
* show that people in the tech community use gpg keys to sign. 
* look at github use of pgp keys.
* gpg vs gpg2
* key vs subkey
* encrypt and decrypt
* digital sign and verify
* import other people's keys
* keyserver
* quantum computers and microsoft visit

## Hash vulnerabilities
We've talked about hashes several times in this class, and used md5sum and maybe discussed sha hashes, sha1 and sha256. I'd be remiss to not mention a hash vulnerability found in git a few years ago. What's the purpose of a hash

SHAttered reference: https://github.blog/2017-03-20-sha-1-collision-detection-on-github-com/

## References
Michael W. Lucas PGP&GPG - email for the practical paranoid
