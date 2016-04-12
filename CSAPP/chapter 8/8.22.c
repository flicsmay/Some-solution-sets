/************************************
 ********  problem 8.22    **********
 ************************************/
 
 
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int mysystem(char *command)
{
    int status;
    char *argv[] = {"sh", "-c", command};
    if (!fork()) {
        // execve has been call and never return 
        execve("/bin/sh", argv, NULL);
        return -1; // if fail to call execve
    }

    if (waitpid(-1, &status, 0) > 0)
        if (WIFEXITED(status) != 0) // if have been sucessful return
            return WEXITSTATUS(status); // return exit status
        else
            return status; 
    return -1;
}


int main(int argc, char *argv[])
{
   printf("%d\n",  mysystem(argv[1]));
}
