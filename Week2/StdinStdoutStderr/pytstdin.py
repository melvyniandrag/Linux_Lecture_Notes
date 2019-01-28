import os
import time
import sys

unbuffered_stdin = os.fdopen(sys.stdin.fileno(), 'rb', buffering=0)

while True:
    x = unbuffered_stdin.read()
    print("received {}".format(x))
