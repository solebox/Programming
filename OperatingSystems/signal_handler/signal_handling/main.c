#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/time.h>
#include <unistd.h>


void handler(int signal){
    alarm(3);
    printf("in signal handler\n");
}
int main()
{
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    sa.sa_handler = handler;

    if (sigaction(SIGALRM, &sa, NULL) < 0)
        abort();
    alarm(3);
    while(1);
    return 0;
}
