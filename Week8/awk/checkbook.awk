BEGIN {
    FS = "\t"
}

NR == 1 {
    print "Beginning Balance \t" $2
    balance = $2
    next
}

{
    print $1, $2, $3
    print balance += $3
}

END {
    print "ending balance\t" balance
}
