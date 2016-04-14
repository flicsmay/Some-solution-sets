#include "shell.h"

extern job_info_ctr job_ctr;
extern job_info *job_lists[MAX_JOBS_NUM];
extern jmp_buf restart_buf;



/*
 * malloc an space to place an initalized job line
 * input(3)	: PID of job & JID of job & command that staring the job(char*)
 * output	: pointer to the alloced space if success
 *			: NULL otherwise
 */
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


/*
 * print out all jobs from job_lines
 */
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

/*
 * find a job in the job lines
 * input(1) : PID of job to found
 * ouput	: JID (which is always grater than 0) if success
 *			: 0 otherwise
 */
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


/*
 * resiger a job to job lines
 * input(2)	: PID of job & INFOMATION of commandline
 * output	: JID of job if success
 *			: 0 otherwise
 */
int resiger_jobs(pid_t pid, char *info)
{
	int jid;

	if (job_ctr.max)
	{
		printf("error : job_list has reach maximum\n");
		return 0;
	}

	jid = 1;

	while (job_lists[jid] != NULL) jid++; // to find a space
	job_lists[jid] = init_job(pid, jid, info);

	job_ctr.num++;
	if (job_ctr.num >= MAX_JOBS_NUM - 1) // since job_list[0] is unused
		job_ctr.max = 1;
	
	return jid;
}

/*
 * remove a job from job line & free the allocated spaces
 * ( by setting the entry pointer to null )
 * input(1)	: PID of job
 * output	: JID of oringial job
 */
void remove_job(pid_t pid)
{
	int i;
	int jid;
	
	for (i = 1; i < MAX_JOBS_NUM; i++)
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
 * input(1) : %JID or PID (char *)
 */
void restart_bg(char *argv)
{
	int num = 0;
	int jid = 0;
	int pid = 0;

	if (argv == NULL)
		return 0;

	if (argv[0] == '%') {
		if ((jid = atoi(++argv)) != 0) {
			if (job_lists[jid]) {
				pid = job_lists[jid]->PID;
				Kill(pid, SIGKILL);
				longjmp(restart_buf, 1);
			}
		}
	}
	else if ((num = atoi(argv)) != 0) {
			jid = find_job(num);
			if (jid != 0) {
				pid = job_lists[jid]->PID;
				Kill(pid, SIGKILL);
				longjmp(restart_buf, 1);
			}
		}
	printf("%s: No such process\n", argv);
}

/* 
 * restart a job in foreground
 * input(1)	: %JID or PID (char *)
 */
int restart_fg(char *argv)
{
	int num = 0;
	int jid = 0;
	int pid = 0;

	if (argv == NULL)
		return 0;

	if (argv[0] == '%') {
		if ((jid = atoi(++argv)) != 0) {
			if (job_lists[jid]) {
				pid = job_lists[jid]->PID;
				Kill(pid, SIGKILL);
				longjmp(restart_buf, 2);
			}
		}
	}
	else if ((num = atoi(argv)) != 0) {
		jid = find_job(num);
		if (jid != 0) {
			pid = job_lists[jid]->PID;
			Kill(pid, SIGKILL);
			longjmp(restart_buf, 2);
		}
	}
	printf("%s: No such process\n", argv);
}

/*
 * initialize the global value
 * job_lists
 * job_ctr
 */
void initi_global(void)
{
	int i;
	for (i = 0; i < MAX_JOBS_NUM; i++)
		job_lists[i] = NULL;

	job_ctr.max = 0;
	job_ctr.num = 0;
	job_ctr.has_frt_job = 0;
}