#include "socketopt.h"

using namespace std;

const int MAXLINE = 20000;
const int LISTENQ = 1000;
typedef struct sockaddr SA;

const int port = 14;

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
