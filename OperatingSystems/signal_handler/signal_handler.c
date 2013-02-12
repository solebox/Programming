#include <signal.h>

void handler(int signal){
    alarm(3);
    prinf("in signal handler\n");
}
int main(void){
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
