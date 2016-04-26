#include "tiny.h"


/*************************************
		ServeStaticPage
**************************************/

static void getFileType(char *filename, char *filetype);

void ServeStaticPage(int targetFD, HttpMessageType *httpMessage, struct stat *statBuf)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXBUF];
	char *fileName = httpMessage->fileName;
	int fileSize = statBuf->st_size;

	/* Send response headers to client */
	getFileType(fileName, filetype);       //line:netp:servestatic:getfiletype
	sprintf(buf, "HTTP/1.0 200 OK\r\n");    //line:netp:servestatic:beginserve
	sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf(buf, "%sContent-length: %d\r\n", buf, fileSize);
	sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
	Rio_writen(targetFD, buf, strlen(buf));       //line:netp:servestatic:endserve

	/* Send response body to client */
	srcfd = Open(fileName, O_RDONLY, 0);    //line:netp:servestatic:open
	srcp = Mmap(0, fileSize, PROT_READ, MAP_PRIVATE, srcfd, 0);//line:netp:servestatic:mmap
	Close(srcfd);                           //line:netp:servestatic:close
	Rio_writen(targetFD, srcp, statBuf->st_size);         //line:netp:servestatic:write
	Munmap(srcp, fileSize);                 //line:netp:servestatic:munmap
}


/*************************************
		ServeDynamicPage
**************************************/

void ServeDynamicPage(int targetFD, HttpMessageType *httpMessage)
{
	char buf[MAXLINE], *emptylist[] = { NULL };
	char *cgiArgs = httpMessage->cgiArguments;
	char *fileName = httpMessage->fileName;

	/* Return first part of HTTP response */
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	Rio_writen(targetFD, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	Rio_writen(targetFD, buf, strlen(buf));

	if (Fork() == 0) { /* child */ //line:netp:servedynamic:fork
		/* Real server would set all CGI vars here */
		setenv("QUERY_STRING", cgiArgs, 1); //line:netp:servedynamic:setenv
		Dup2(targetFD, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:servedynamic:dup2
		Execve(fileName, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
	}
	Wait(NULL); /* Parent waits for and reaps child */ //line:netp:servedynamic:wait
}

void getFileType(char *filename, char *filetype)
{
	if (strstr(filename, ".html"))
		strcpy(filetype, "text/html");
	else if (strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");
	else if (strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpeg");
	else
		strcpy(filetype, "text/plain");
}