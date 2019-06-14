import sys
import time

x = 1
while( True ):
    sys.stdout.write("{}\n".format(x) )
    x += 1 
    time.sleep(2)
