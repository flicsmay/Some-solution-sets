/*************************************
 *****       Problem 8.24       ******
 *************************************/

#include <signal.h>
#include "csapp.h"
#define	N	2

int main()
{
	int status, i;
	pid_t pid;
	char erro_info
	
	for (i = 0; i < N; i++)
		if ((pid = Fork()) == 0)
			exit(100+i);
		
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status=%d\n",
				pid, WEXITSTATUS(status));
		else
		{
			if (WIFSIGNALED(status))
			{
				printf("child %d terminated by signal %d:", pid, WTERMSIG(status));
				psignal(WTERMSIG(status), erro_info);
			}	
			else
				printf("child %d terminated abnormally\n");
		}
	}
		
	if (errno != ECHILD)
		unix_error("waitpid error");
		
	exit(0);
}