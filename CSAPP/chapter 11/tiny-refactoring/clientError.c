#include "tiny.h"


/***********************************
		ClientError
***********************************/

void ClientError(int targetFD, char *cause,
	char* errorNumber, char *shortMessage, char *longMessage)
{
	char buf[MAXLINE], body[MAXBUF];

	/* Build the HTTP response body */
	sprintf(body, "<html><title>Tiny Error</title>");
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf(body, "%s%s: %s\r\n", body, errorNumber, shortMessage);
	sprintf(body, "%s<p>%s: %s\r\n", body, longMessage, cause);
	sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

	/* Print the HTTP response */
	sprintf(buf, "HTTP/1.0 %s %s\r\n", errorNumber, shortMessage);
	Rio_writen(targetFD, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	Rio_writen(targetFD, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	Rio_writen(targetFD, buf, strlen(buf));
	Rio_writen(targetFD, body, strlen(body));
}