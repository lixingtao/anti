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
#include <fcntl.h> 

using namespace std;

const int MAXLINE = 20000;
const int LISTENQ = 1000;
typedef struct sockaddr SA;

const int port = 14;

int readline(int fd, void *vptr, const size_t maxlen) {
    ssize_t n, rc;
    char c, *ptr;
    ptr =(char *) vptr;
    for(n = 1; n < maxlen; n++) {
        rc = read(fd, &c, 1);
        if (rc == 1) {
            *ptr++ = c;
            if (c == '\n') break;
        } else if (rc == 0){
            *ptr = 0;
            return n-1;
        } else {
            return -1;
        }
    }
    *ptr = 0;
    return n;
}

int write_format(int fd, void *vptr, int len) {
    char len_c[4];
    int ret = 0;

    *(int *)len_c = len;
    ret = write(fd,len_c, 4);
    if (ret < 0) return ret;

    ret = write(fd, vptr, strlen((char*)vptr));
    return ret;
}


//读取的前四个字节记录后面字符的个数，所以总长度应该大于等于4
int  read_format(int fd, void *vptr) {
    int ret = 0;
    ret = read(fd, vptr, 4);
    if (ret < 0) return ret;

    int len = *(int*)vptr;
    ret = read(fd, vptr, len);
    return ret;
}

int main(int argc,char *argv[])
{
    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    for(;;) {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (SA*) &cliaddr, &len);

        int readlen;
        int writelen;
        char readbuf[MAXLINE];
        char writebuf[MAXLINE];
        //read读取的是时候不会再目的字符串中添加终止符
        //read读取不超过第三个参数的数据到readbuf中
        /*while((readlen = read(connfd, readbuf, 2)) > 0) {
          readbuf[readlen] = 0;
          printf("%s**\n", readbuf);
          fflush(stdout);
          sleep(5);
          }*/
        //while((readlen = readline(connfd, readbuf, MAXLINE)) > 0) {
        while((readlen = read_format(connfd, readbuf)) > 0) {
            printf("%s", readbuf);
            fflush(stdout);
        }
        printf("finish \n");
        fflush(stdout);
    }
    return 0;
    }
