#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <list>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netdb.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>  
#include <errno.h>  
#include <malloc.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <sys/ioctl.h>  
#include <stdarg.h>  
#include <fcntl.h>  

using namespace std;

const int MAXLINE = 2000;
const int LISTENQ = 1000;
typedef struct sockaddr SA;

const int port = 14;
char ip_addr[20] = "127.0.0.1";

int main(int argc,char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    int readlen;
    int writelen;
    char readbuf[MAXLINE];
    char writebuf[MAXLINE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr, &servaddr.sin_addr);

    connect(sockfd, (SA*) &servaddr, sizeof(servaddr));

    snprintf(writebuf, MAXLINE, "hello world");
    write(sockfd, writebuf, sizeof(writebuf));
    return 0;
}
