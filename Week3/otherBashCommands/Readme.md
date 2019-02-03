# Other Bash Commands

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
