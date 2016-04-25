#include "csapp.h"


void handleRequireFromClient(int connectedFD);


int main(int argc, char **argv)
{
	int listenFD;
	int connectedFD;
	int portNumber;
	int clitenAddressLength;
	struct sockaddr_in clientAddress;

	if (argc != 2) { // if no a port inputed
		fprintf(stderr, "usage: %s <prot>\n", argv[0]);
		exit(1);
	}
	portNumber = atoi(argv[1]);

	listenFD = Open_listenfd(portNumber); // listen the specific port

	for (;;) { // keep accepting the require
		clitenAddressLength = sizeof(clientAddress);
		connectedFD = Accept(listenFD, (SA*)&clientAddress, &clitenAddressLength);
		handleRequireFromClient(connectedFD);
		Close(connectedFD);
	}
}


void handleRequireFromClient(int connectedFD)
{
	int isStaticRequires;
	struct stat sbuf;

}