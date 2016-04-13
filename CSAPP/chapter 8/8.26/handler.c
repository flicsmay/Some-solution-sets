#include "shell.h"

void int_handler(int sig);
void tstp_handler(int sig);
void chld_handler(int sig);
void cont_handler_child(int sig);
void int_handler_child(int sig);
void tstp_handler_child(int sig);

extern sigjmp_buf restart_buf;

extern job_info_ctr job_ctr;
extern job_info *job_lists[MAX_JOBS_NUM];

void resiger_signal(void)
{
	Signal(SIGINT, int_handler);
	Signal(SIGTSTP, tstp_handler);
	Signal(SIGCHLD, chld_handler);
}


void int_handler(int sig)
{
	if (job_ctr.has_frt_job)
		Kill(-FRONT_GOUP_ID, SIGINT);
}

void tstp_handler(int sig)
{
	if (job_ctr.has_frt_job)
		Kill(-FRONT_GOUP_ID, SIGTSTP);
}


void chld_handler(int sig)
{
	pid_t pid;
	int status;
	char *erro_info;

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
				printf("child %d terminated abnormally\n", pid);
		}
	}
}


void set_sig_handler_child(void)
{
	Signal(SIGINT, int_handler_child);
	Signal(SIGTSTP, tstp_handler_child);
	Signal(SIGCONT, cont_handler_child);
}


void cont_handler_child(int sig)
{
	siglongjmp(restart_buf, 1);
}


void int_handler_child(int sig)
{
	pid_t pid = getpid();
	int jid = 0;

	jid = find_job(pid);
	printf("Job [%d] %d stopped by signal :", jid, pid);
	psignal(sig, NULL);
	Pause();
}


void tstp_handler_child(int sig)
{
	pid_t pid = getpid();
	int jid = 0;

	jid = find_job(pid);
	printf("Job [%d] %d terminated by signal :", jid, pid);
	psignal(sig, NULL);
	exit(0);
}