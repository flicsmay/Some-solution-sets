#include "shell.h"

extern job_info_ctr job_ctr;
extern job_info *job_lists[MAX_JOBS_NUM];

job_info *init_job(pid_t pid, int jid, char *info)
{
	job_info * p;

	p = (job_info*)malloc(sizeof(job_info));
	if (p == NULL) {
		printf("error: fail to malloc job infomation\n");
		exit(0);
	}

	p->PID = pid;
	p->JID = jid;
	strncpy(p->info, info, MAX_INFO_SAVED-1);
	p->info[MAX_INFO_SAVED - 1] = '\0';
	return p;
}


void print_jobs()
{
	int i;

	for (i = 1; i < MAX_JOBS_NUM; i++)
		if (job_lists[i])
		{
			printf("[%d] %d  %s\n", job_lists[i]->JID,
				job_lists[i]->PID, job_lists[i]->info);
		}
}


int find_job(pid_t pid)
{
	int i;

	for (i = 1; i < MAX_JOBS_NUM; i++)
	{
		if (job_lists[i] && (job_lists[i]->PID == pid))
			return i;
	}
	return 0;
}



int resiger_job(pid_t pid, char *info)
{
	int jid;

	if (job_ctr.max)
	{
		printf("error : job_list has reach maximum\n");
		return 0;
	}

	jid = job_ctr.last;

	while (job_lists[jid])
	{
		jid++;
		if (jid >= MAX_JOBS_NUM)
			jid = 1;
	}
	job_lists[jid] = init_job(pid, jid, info);

	job_ctr.num++;
	job_ctr.last = jid;
	if (job_ctr.num == MAX_JOBS_NUM)
		job_ctr.max = 1;
	
	return jid;
}

int remove_job(pid_t pid)
{
	int i;
	int jid;
	
	for (i = 0; i < MAX_JOBS_NUM; i++)
	{
		if (job_lists[i] && (job_lists[i]->PID == pid)) {
			jid = job_lists[i]->JID;
			free(job_lists[i]);
			job_lists[i] = NULL;
			break;
		}
	}

	job_ctr.num--;
	job_ctr.max = 0;
	return jid;
}


/*
 * restart a process in background
 * input prototype : %JID or PID (int)
 * output	: JID of the background proc
 *			: 0 otherwises
 */
int restart_bg(char *argv)
{
	int num = 0;
	int jid = 0;
	int pid = 0;

	if (argv == NULL)
		return 0;

	if (argv[0] == '%') {
		if ((jid = atoi(++argv)) != 0) {
			pid = job_lists[jid]->PID;
			Kill(pid, SIGCONT);
			return pid;
		}
	}
	else if ((num = atoi(argv)) != 0) {
			jid = find_job(num);
			if (jid != 0) {
				pid = job_lists[jid]->PID;
				Kill(pid, SIGCONT);
				return pid;
			}
		}
	printf("%s: No such process\n", argv);
	return 0;
}


int restart_fg(char *argv)
{
	int pid = 0;
	int status = 0;
	if ((pid = restart_bg(argv)) != 0)
		Waitpid(pid, &status, 0);
	return pid;
}