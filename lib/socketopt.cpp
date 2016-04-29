#include "socketopt.h"

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

int readn(int fd, void *vptr, int n) {
    int nleft = n;
    int nread;

    char *ptr = (char*) vptr;
    while(nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) nread = 0;
            else return -1;
        } else if (nread == 0) 
            break;
        ptr += nread;
        nleft -= nread;
    }
    return n - nleft;
}

int writen(int fd, const void *vptr, int n) {
    int nleft = n;
    int nwrite;
    const char * ptr = (const char *) vptr;

    while(nleft > 0) {
        if ((nwrite = write(fd, ptr, nleft)) <= 0) {
            if (nwrite < 0 && errno == EINTR) nwrite = 0;
            else  return -1;
        }
        nleft -= nwrite;
        ptr += nwrite;
    }
    return n;
}
