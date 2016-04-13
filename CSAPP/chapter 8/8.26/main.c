#include "shell.h"


job_info_ctr job_ctr;
job_info *job_lists[MAX_JOBS_NUM];
sigjmp_buf restart_buf;



int main()
{
	char cmdline[MAXLINE];
	job_ctr.max = 0;
	job_ctr.num = 0;
	job_ctr.last = 1;
	job_ctr.has_frt_job = 0;

	resiger_signal();
	while (1)
	{
		printf("> ");
		Fgets(cmdline, MAXLINE, stdin);
		
		if (feof(stdin))
			exit(0);

		eval(cmdline);
	}
}


void eval(char *cmdline)
{
	char *argv[MAX_ARGMENT_GET];
	char buf[MAXLINE];
	int status;
	int bg;
	int jid;
	pid_t pid;

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;

	// if isn't builtin command
	if (!builtin_command(argv)) {
		if ((pid = Fork()) == 0) { // fork a process
			if (!bg)
				Setpgid(getpid(), FRONT_GOUP_ID);
			set_sig_handler_child();
			jid = resiger_job(pid, buf);
			sigsetjmp(restart_buf, 1);
			if (execve(argv[0], argv, environ) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}

		if (!bg) {
			job_ctr.has_frt_job = 1;
			status = 0;
			if (waitpid(pid, &status, 0) < 0)
				unix_error("waitfg: waitpid error");
		}
		else
			printf("[%d] %d	  %s", jid, pid, cmdline);
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