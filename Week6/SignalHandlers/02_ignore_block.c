/*
 * A simple example program demonstrating signal handlers.
 * This simple program also illustrates how C programs return values
 * to bash.
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define MY_EXIT_TERM 100
#define MY_EXIT_INT 101

static volatile int keep_running_int = 1;
static volatile int keep_running_term = 1;

static void sig_handler_int(int i)
{
    (void) i;
    keep_running_int = 0;
}

static void sig_handler_term(int i)
{
    (void) i;
    keep_running_term = 0;
}

int main(void)
{
    signal(SIGINT,  sig_handler_int);
    signal(SIGTERM, sig_handler_term);

    while ( ( keep_running_int) && ( keep_running_term ) ) {
        puts("Still running...");
    }

    if( !keep_running_term ){
        puts("Received SIGTERM!");
        return MY_EXIT_TERM;
    }
    else if ( !keep_running_int ){
        puts("Received SIGINT!");
        return MY_EXIT_INT;
    }
    // You should never see EXIT_SUCCESS, we're trapped in the
    // while loop unless we get SIGINT, SIGTERM, or SIGKILL
    return EXIT_SUCCESS;
}
