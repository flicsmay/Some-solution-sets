#include "tiny.h"


static void readFullHttpRequest(int targetFD, HttpMessageType *httpMessage);
static void checkHttpRequest(int targetFD, HttpMessageType *httpMessage);
static void handleHttpRequest(int targetFD, HttpMessageType *httpMessage);

void ServeAClient(int targetFD, struct sockaddr_in *clientAddressInfo)
{
	HttpMessageType httpMessage;

	readFullHttpRequest(targetFD, &httpMessage);
	checkHttpRequest(targetFD, &httpMessage);
	handleHttpRequest(targetFD, &httpMessage);
}


/***********************************
		readFullHttpRequest
 ***********************************/

static void readHttpRequestLine(rio_t *rio, HttpMessageType *httpMessage);
static void readHttpRequestHeader(rio_t *rio, HttpMessageType *httpMessage);

static void readFullHttpRequest(int targetFD, HttpMessageType *httpMessage)
{
	rio_t rio;

	Rio_readinitb(&rio, targetFD);
	readHttpRequestLine(&rio, httpMessage);
	readHttpRequestHeader(&rio, httpMessage);
}


/*************************************
		checkHttpRequest
**************************************/

static void checkHttpRequest(int targetFD, HttpMessageType *httpMessage)
{
	if (strcasecmp(httpMessage->method, "GET")) {// support GET ONLY
		ClientError(targetFD, httpMessage->method, "501", "Not Implemented",
			"Tiny does not implement this method");
		return;
	}
}


/*************************************
		handleHttpRequest
**************************************/

static int parseURI(HttpMessageType *httpMessage);
static int isFileReadable(struct stat *statBuf);
static int isFileExecutable(struct stat *statBuf);

static void handleHttpRequest(int targetFD, HttpMessageType *httpMessage)
{
	int isStatic;
	struct stat statBuf;

	isStatic = parseURI(httpMessage);
	if (stat(httpMessage->fileName, &statBuf) < 0) {
		ClientError(targetFD, httpMessage->fileName, "404", "Not found",
			"Tiny couldn't find this file");
		return;
	}

	if (isStatic) {
		if (!isFileReadable(&statBuf)) {
			ClientError(targetFD, httpMessage->fileName, "403", "Forbidden",
				"Tiny couldn't read the file");
			return;
		}

		ServeStaticPage(targetFD, httpMessage, &statBuf);
	}
	else {
		if (!isFileExecutable(&statBuf)) {
			ClientError(targetFD, httpMessage->fileName, "403", "Forbidden",
				"Tiny couldn't run the CGI program");
			return;
		}

		ServeDynamicPage(targetFD, httpMessage);
	}
}


/*************************************
		other functions
**************************************/

static void readHttpRequestLine(rio_t *rio, HttpMessageType *httpMessage)
{
	char buf[MAXLINE];

	Rio_readlineb(rio, buf, MAXLINE);
	sscanf(buf, "%s %s %s", httpMessage->method, httpMessage->URI, httpMessage->version);
}

static void handleHttpRequestHeader(char *buf, HttpMessageType *httpMessage)
{	// do nothing 
	return;
}

static void readHttpRequestHeader(rio_t *rio, HttpMessageType *httpMessage)
{
	char buf[MAXLINE];

	Rio_readlineb(rio, buf, MAXLINE);
	while (strcmp(buf, "\r\n")) {
		handleHttpRequestHeader(buf, httpMessage);
		Rio_readlineb(rio, buf, MAXLINE);
		printf("%s\n", buf);
	}
	return;
}

static int parseURI(HttpMessageType *httpMessage)
{
	char *cgiArgs = httpMessage->cgiArguments;
	char *URI = httpMessage->URI;
	char *fileName = httpMessage->fileName;
	char *ptr;

	if (!strstr(URI, "cgi-bin")) {
		strcpy(cgiArgs, "");
		strcpy(fileName, ".");
		strcat(fileName, URI);
		if (URI[strlen(URI) - 1] == '/')
			strcat(fileName, "home.html");
		return 1;
	}
	else {
		ptr = index(URI, '?');
		if (ptr) {
			strcpy(cgiArgs, ptr + 1);
			*ptr = '\0';
		}
		else
			strcpy(cgiArgs, "");

		strcpy(fileName, ".");
		strcat(fileName, URI);
		return 0;
	}
}

static int isFileReadable(struct stat *statBuf)
{
	return ((S_ISREG(statBuf->st_mode)) && (S_IRUSR & statBuf->st_mode));
}

static int isFileExecutable(struct stat *statBuf)
{
	return ((S_ISREG(statBuf->st_mode)) && (S_IXUSR & statBuf->st_mode));
}