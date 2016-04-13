#ifndef _SHELL_H
#define _SHELL_H

#include "csapp.h"

#define		MAX_ARGMENT_GET			128
#define		MAX_JOBS_NUM			64
#define		MAX_INFO_SAVED			128
#define		FRONT_GOUP_ID			20

typedef struct Job_Info_CTR
{
	int max;
	int num;
	int last;
	int has_frt_job;
}job_info_ctr;

typedef struct Job_Info
{
	pid_t PID;
	int JID;
	char info[MAX_INFO_SAVED];
}job_info;


void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
job_info *init_job(pid_t pid, int jid, char *info);
int resiger_job(pid_t pid, char *info);
int remove_job(pid_t pid);
void print_jobs(void);
int find_job(pid_t pid);
void set_sig_handler_child(void);
int restart_bg(char *argv);
int restart_fg(char *argv);


#endif