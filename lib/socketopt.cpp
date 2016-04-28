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
