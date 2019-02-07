# Other Bash Commands

We've covered a good amount of bash commands so far in this class, there's still a few more cool Unix/Linux tools to talk about, but you're quite knowledgable about bash/Linux already. Today I'm going to add a few more programs to your toolkit.

## date

What's the date/time?

```
$ date
Sun Feb  3 10:23:17 EST 2019
```

## watch
Keep updating the output of a given command every n seconds.

```
watch -n1 date
```

This will keep updating the time in the terminal every second.
Try stopping watch with CTRL+Z and restarting it with fg. Try killing it with CTRL+C

## tail

```
tail FILE
```

shows you the last few lines in the file.

```
tail -n2 FILE
```

shows you the last 2 lines in the file.

## head

```
head FILE
```

shows you the first few lines in a file.

```
head -n10
```

shows you the first 10.

## a pipe using head and tail

```
head -n2 FILE | tail -n1 
```

shows you the second line in the file. See how useful pipes are?!?!?
