#ifndef _TINY_H
#define _TINY_H

#include "csapp.h"

typedef struct HttpMessage
{
	char method[MAXLINE];
	char URI[MAXLINE];
	char version[MAXLINE];
	char fileName[MAXLINE];
	char cgiArguments[MAXLINE];

	// more elements to be added

}HttpMessageType;


void ServeAClient(int targetFD, struct sockaddr_in *clientAddressInfo);
void ClientError(int targerFD, char *cause,
	char* errorNumber, char *shortMessage, char *longMessage);
void ServeStaticPage(int targetFD, HttpMessageType *httpMessage, struct stat *statBuf);
void ServeDynamicPage(int targetFD, HttpMessageType *httpMessage);

#endif