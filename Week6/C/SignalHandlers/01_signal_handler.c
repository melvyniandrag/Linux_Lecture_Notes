/*
 * A simple example program demonstrating signal handlers.
 *
 *
 *
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

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
    }
    if ( !keep_running_int ){
        puts("Received SIGINT!");
    }
    return EXIT_SUCCESS;
}
