#include "shell.h"


job_info_ctr job_ctr;
job_info *job_lists[MAX_JOBS_NUM];
jmp_buf restart_buf;



int main()
{
	char cmdline[MAXLINE];

	initi_global();	// initial the global var
	resiger_signal();  // resiger signal

	while (1)
	{
		printf("> ");
		Fgets(cmdline, MAXLINE, stdin);
		
		if (feof(stdin))
			exit(0);

		eval(cmdline); // evaluate comandline
	}
}


void eval(char *cmdline)
{
	char *argv[MAX_ARGMENT_GET];
	char buf[MAXLINE];
	int status;
	int bg;
	pid_t pid;
	int rc;

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;

	// if isn't builtin command
	if (!builtin_command(argv)) {

		rc = setjmp(restart_buf); // set signal jump destination
		if (rc == 1)
			bg = 0;
		if (rc == 2)
			bg = 1;
		if ((pid = Fork()) == 0) {
			Setpgid(getpid(), getpid()); // get each child a unique group
			if (execve(argv[0], argv, environ) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}

		job_ctr.jid = resiger_jobs(pid, buf); // resiger to get a JID
		job_ctr.pid = pid;	// get pid to sent signal when a int or stop sig coming
		if (!bg) {
			job_ctr.has_frt_job = 1;	// set has_front_job signed
			status = 0;
			Waitpid(pid, &status, 0);
			remove_job(pid);			// remove job after reap
		}
		else
			printf("[%d] %d	  %s", job_ctr.jid, pid, cmdline);
	}
	job_ctr.has_frt_job = 0;
	return;
}


int builtin_command(char **argv)
{
	if (!strcmp(argv[0], "jobs")) {
		print_jobs();
		return 1;
	}


	if (!strcmp(argv[0], "quit"))
		exit(0);


	if (!strcmp(argv[0], "bg")) {
		restart_bg(argv[1]);
		return 1;
	}


	if (!strcmp(argv[0], "fg")) {
		restart_fg(argv[1]);
		return 1;
	}


	if (!strcmp(argv[0], "&"))
		return 1;
	return 0;
}


int parseline(char *buf, char **argv)
{
	char *delim;
	int	argc;
	int bg;

	// replace '\n' with space
	buf[strlen(buf) - 1] = ' ';
	while (*buf && (*buf == ' ')) // Ignore leading spaces
		buf++;

	argc = 0;
	while ((delim = strchr(buf, ' ')))
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) // Ignore spaces
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0) // Ignore blank line
		return 1;

	/* Should the job run in the back ground? */
	if ((bg = (*argv[argc - 1] == '&')) != 0)
		argv[--argc] = NULL;

	return bg;
}