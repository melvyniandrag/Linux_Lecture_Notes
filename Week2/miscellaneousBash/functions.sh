hello_world(){
    echo "hello world"
}

hello_you(){
    echo "hello $1"
}

I_have_a_retval(){
    # no way to return a string. Bash knows about return codes and strings written to stdout, stderr.
    return 1
}

hello_world
hello_you melvyn
hello_you $(whoami)
I_have_a_retval
echo $?
