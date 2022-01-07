#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BACKLOG 5
#define MAX_BUFFER_SIZE 2048

/* Function forward references */

//server.c
void serveOneClient(int clientFd);

//client.c
void doClientRequest(int serverFd);

//connect.c
int errorCheck(int rtnVal, const char *message);
void connectServer(int *serverSok);
void acceptConnect(int serverSok, int *clientSok);
void connectClient(int *serverSok);
