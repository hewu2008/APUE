/**
 * 信号处理中调用不可重入函数
 */
#include "../include/apue.h"
#include <pwd.h>

static void my_alarm(int signo)
{
	struct passwd *rootptr;
	printf("in signal handler\n");
	if ((rootptr = getpwnam("root")) == NULL) 
		err_sys("getpwnam(root) error");
	alarm(1);
}

int main(int argc, char const *argv[])
{
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);
	for (; ;) {
		if ((ptr = getpwnam("sar")) == NULL) 
			err_sys("getpwnam error");
		if (strcmp(ptr->pw_name, "sar") != 0)	
			printf("return value corrupted! pw_name=%s\n", ptr->pw_name);
	}
	return 0;
}
