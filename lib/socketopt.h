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

#endif
