#ifndef SOCKETOPT
#define SOCKETOPT

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
#include <poll.h>

typedef struct sockaddr SA;

int readline(int fd, void *vptr, const size_t maxlen); 
int write_format(int fd, void *vptr, int len); 
//读取的前四个字节记录后面字符的个数，所以总长度应该大于等于4
int  read_format(int fd, void *vptr); 

//在套接字非阻塞的情况下，当写入数据量超过，写入缓冲区或者缓冲区满的时候，read不能将全部n个字节全部写入，而是写入小于n的字节并返回写入的字节数
//下面两行可以设置套接字非阻塞
//int flags=fcntl(sockfd,F_GETFL,0);
//fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);//设置为非阻塞
int readn(int fd, void *vptr, int n);

//类似与readn
int writen(int fd, const void *vptr, int n);
#endif
