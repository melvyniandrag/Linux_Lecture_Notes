import sys, select

while True:
    i, output, error = select.select( [sys.stdin], [], [], 5 )
    if ( i ):
        print("received {}".format( sys.stdin.readline().strip() ) )
    else:
        continue
