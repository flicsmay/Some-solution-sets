/************************************
 ********  Problem 8.25  ************
 ************************************/

#include "csapp.h"

static sigjmp_buf tfgets_jmp_buf;

// if without a input more than 5s then return NULL
char *tfgets(char *buf, int bufsize, FILE *stream)
{
    Signal(SIGALRM, tfget_handler);

    if (!sigsetjmp(tfgets_jmp_buf, 1))
        // if the tfgets return then the signal will be discard ?
        return fgets(buf, bufsize, stream); 
    // if there are no a return in 5s
    return NULL; 
}

static void tfget_handler(int sig)
{
    siglongjmp(tfgets_jmp_buf, 1);
}
