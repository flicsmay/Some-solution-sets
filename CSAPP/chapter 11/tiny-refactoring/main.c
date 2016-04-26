
#include "tiny.h"

static void checkArgument(int argc, char **argv);
static int getPortNumber(int argc, char **argv);
static void serveClients(int listenedFD);
static int sigChildHandler(int sig);

int main(int argc, char **argv)
{
	int portNumber;
	int listenedFD;

	checkArgument(argc, argv);
	Signal(SIGCHLD, sigChildHandler);

	portNumber = getPortNumber(argc, argv);

	listenedFD = Open_listenfd(portNumber);

	for (;;) 
		serveClients(listenedFD);
}


/***********************************************
		checkArgument
***********************************************/

static int isArgumentCorrect(int argc, char **argv);
static void argumentError(FILE *targetFile, int argc, char **argv);

static void checkArgument(int argc, char **argv)
{
	if (!isArgumentCorrect(argc, argv)) {
		argumentError(stderr, argc, argv);
		exit(1);
	}
}


/***********************************************
		getPortNumber
***********************************************/

static int getPortNumber(int argc, char **argv)
{
	return atoi(argv[1]);
}


/***********************************************
		serveClients
***********************************************/

static int acceptConnectedFD(int listenedFD, struct sockaddr_in *clientAddressInfo);

static void serveClients(int listenedFD)
{
	int connectedFD;
	struct sockaddr_in clientAddressInfo;

	connectedFD = acceptConnectedFD(listenedFD, &clientAddressInfo);

	ServeAClient(connectedFD, &clientAddressInfo);
	Close(connectedFD);
}

/***********************************************
		sigChildHandler
***********************************************/

static int sigChildHandler(int sig)
{
	int status;
	Waitpid(-1, &status, 0);
	printf("handler has successful reap a child\n");
}

/***********************************************
		other functions
***********************************************/

static int isArgumentCorrect(int argc, char **argv)
{
	if (argc == 2)
		return 1;
	else
		return 0;
}


static void argumentError(FILE *targetFile, int argc, char **argv)
{
	fprintf(targetFile, "usage: %s <port>\n", argv[0]);
}


static int acceptConnectedFD(int listenedFD, struct sockaddr_in *clientAddressInfo)
{
	int clientAdresslength = sizeof(clientAddressInfo);

	return Accept(listenedFD, (SA*)clientAddressInfo, &clientAdresslength);
}
