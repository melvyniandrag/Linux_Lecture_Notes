#
# Expect an error, you cant use -lt with strings, only numbers.
#
x1=1a
x2=2a
if [ $x1 -lt $x2 ]        
then
    echo "$x1 < $x2"
else
    echo "$x2 <= $x1"
fi
