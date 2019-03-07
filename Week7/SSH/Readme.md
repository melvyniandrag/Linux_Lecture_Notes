# SSH
SSH is the secure shell. It's a tool you use to connect to remote machines. Weve already been using ssh for about a month and a half now, so you know a bit about it. We've been using it without a password from the browser when we click the 'ssh' button to get into our google machine. We've been able to enable password authentication t oget into our machines from a terminal using a password.

## Encryption

A short story time before learning the tools.

Reference: https://www.digitalocean.com/community/tutorials/understanding-the-ssh-encryption-and-connection-process

To prepare for encryption:
Take a number theory class.
Take all the other math classes.

Used to be illegal. There is a long story about the legality of encryption in the USA. Certain types of encryption algorithms are considered military grade weapons. Due to a long legal battle that was ultimately unresolved, we can use encryption. But the US government ( or another government ) can pick up the battle again and make eencryption illegal in their country. How this affects SSH is another topic of discussion.

In general there are alot of Linux tools that use encryption.

Tweet NaCl:
https://tweetnacl.cr.yp.to/ ( available anywhere in the world that has twiter! The tweets are actual encryption code. Did bernstein break the law by tweeting these things? )

## Asymmetric vs Symmetric encryption vs hashing

### Asymmetric
It's also called public key cryptography. You generate two keys. One public and one private. You can send the public to anyone, it's no secret. But the private one you must protect 100%, the integrity of the encryption depends on it. 

You give the public key out - people can send you encrypted messages using the public key. 
The only way to decrypt these messages is with the private key. ssh uses asymmetric encryption. You create a key pair, put the public key on the server you want to log into and keep the private key on your laptop or whatever device you use to perform the remote log in.

There are a number of different asymmeteric encryption algorithms. They keys can be different sizes ,and this depends on the algorithm. https://www.ssh.com/ssh/keygen/

A pictorial explanation.
https://en.wikipedia.org/wiki/Public-key_cryptography#/media/File:Public_key_encryption.svg

### Symmetric

Very interesting stuff, but there's no time to tell you about it. I got to study the Elliptic Curve Diffie Hellman algorithm for a while and it is super interesting stuff. Both parties have the same key and use it for both encryption and decryption.

### Hashing

What is a hash. Some examples.

There are some cool hash collisions out there.
https://www.theregister.co.uk/2017/02/23/google_first_sha1_collision/
https://stackoverflow.com/questions/10434326/hash-collision-in-git

## How to generate an ssh key
Remember that ssh keys come in pairs. The server holds the public keys of those that can connect to it. The clients all hold their own private keys. We are sshing into the cloud machines without having to enter our passwords - that means our public keys must be on there. public keys are stored in `/home/$(whoami)/.ssh/authorized_keys`. Check out your keys:

```
cat /home/$(whoami)/.ssh/authorized_keys
```

use `ssh-keygen`. The `-t` parameter specifies the algorithm. The `-b` parameter specifies the size of the key.

```
$ssh-keygen -t rsa -b 4096
```

Then you'll see we have keys. Add the key to another vm and we'll ssh into that machine. Also add the key to github and then we'll be able to push commits without a password.

To be able to ssh-copy-id we need to be able to ssh in with password. Temporarily set the sshd config on the target machine to allow password auth so you can use ssh-copy-id. Then turn it off again.

## Uses of ssh
* get into your server without using your password.
* make git commits without using your password.
