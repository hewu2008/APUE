/**
 * 捕捉SIGUSR1和SIGUSR2的简单程序
 */
#include "../include/apue.h"

/* one handler for both signals */
static void sig_usr(int); 

int main(int argc, char const *argv[])
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR) 
		err_sys("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR) 
		err_sys("can't catch SIGUSR2");
	for (; ;)
		pause();
	return 0;
}

static void sig_usr(int signo) 
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		err_dump("received signal %d\n", signo);
}