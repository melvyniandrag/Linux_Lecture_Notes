#
# More syntax issues, but no logical issues.
# This will error. you need to use either escape the < with a \< or use [[]]
#
#
# The old bash advice is to double quote all variables in bash to make sure they are interpreted as a single value.
# 
# notice the difference between how this script runs with bash and with sh
#
# sh is the bourne shell, bash is the bourne again shell
#

x1=1a
x2=2a

if [[ "$x1" < "$x2" ]]
then
    echo "$x1 < $x2"
else
    echo "$x2 <= $x1"
fi

if [ "$x1" \< "$x2" ]        
then
    echo "$x1 < $x2"
else
    echo "$x2 <= $x1"
fi
