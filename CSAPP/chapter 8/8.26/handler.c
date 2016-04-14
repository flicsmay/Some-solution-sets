#include "shell.h"

void int_handler(int sig);
void tstp_handler(int sig);
void chld_handler(int sig);
void cont_handler_child(int sig);
void int_handler_child(int sig);
void tstp_handler_child(int sig);


extern job_info_ctr job_ctr;
extern job_info *job_lists[MAX_JOBS_NUM];


/*
 * resiger signal
 * SIGINT SIGTSTP SIGCHLD
 */
void resiger_signal(void)
{
	Signal(SIGINT, int_handler);
	Signal(SIGTSTP, tstp_handler);
	Signal(SIGCHLD, chld_handler);
}

// signal SIGINT handler
void int_handler(int sig)
{
	char errinfo[128];

	if (job_ctr.has_frt_job)
		Kill(-(job_ctr.pid), SIGINT);
	printf("Job [%d] %d stopped by signal :", job_ctr.jid, job_ctr.pid);
	psignal(sig, errinfo);
	printf("\n");
}

// signal TSTP handler
void tstp_handler(int sig)
{
	char errinfo[128];

	if (job_ctr.has_frt_job)
		Kill(-(job_ctr.pid), SIGTSTP);
	printf("Job [%d] %d terminated by signal :", job_ctr.jid, job_ctr.pid);
	psignal(sig, errinfo);
	printf("\n");
}

// to reap children & printf status info
void chld_handler(int sig)
{
	pid_t pid;
	int status;
	char *erro_info;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		remove_job(pid);	// remove jobs from list after reap it 
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
				printf("child %d terminated abnormally\n", pid);
		}
	}
}