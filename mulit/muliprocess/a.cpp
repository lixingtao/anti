#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#define SEM_KEY1 5555
#define MY_SHM_ID 67483
union semun
{
    int setval;
    struct semid_ds *buf;
    unsigned short *array;
};

void print_arr(unsigned short const*p) {
    printf("%d\t%d\n", p[0], p[1]);
}

int main()
{
    int shmid,semid;
    int *addr;
    int h=0,w=0;
    int ret;
    union semun sem_args;
    unsigned short array[2]={0,1};
    sem_args.array=array;
    //shmid=shmget(MY_SHM_ID,getpagesize(),IPC_CREAT);
    //shmid=shmget(ftok("in.dat",1001),getpagesize(),0);
    //获取共享内存id
    if((shmid=shmget(MY_SHM_ID,getpagesize(),IPC_CREAT))==-1)
    {
        perror("shmget error:");
        exit(EXIT_FAILURE);
    }
    //获取信号量id
    //semget, int semget(key_t key, int nsems, int semflg), key:信号量的键值，多个进程可以通过它访问同一个信号量
    //semflg，同open函数的权限位，可以用八进制表示法，其中使用IPC_CREAT标志创建新的信号量，即使该信号量已经存在（具有同一个键值的信号量已经在系统中存在），也不会出错。如果同时使用IPC_PRIVATE标志可以创建一个新的唯一的信号量，如果该信号量已经在系统中存在，该函数会返回错误
    //函数返回值，如果出错返回-1
    semid=semget(SEM_KEY1,2,IPC_CREAT|0666); 
    if(semid==-1)
    {
        perror("semget error:");
        exit(EXIT_FAILURE);
    }

    //semctl(int semid, int semnum, int cmd, union semun arg)
    //semid 信号量集标识符
    //semnum 信号量集数组上的下标，表示某一个信号量
    //cmd 
    //arg
    // union semun {
    //  short val; //SETVAL用的值
    //  struct semid_ds * buf; //IPC_STAT，IPC_SET用的semid_ds结构
    //  unsigned short * array; //SETALL, GETALL用的值
    //  struct seminfo *buf; //为控制IPC_INFO提供的缓存
    // };
    ret=semctl(semid,1,SETALL,sem_args);
    printf("%d\n", sem_args.setval);
    printf("%d\n", semctl(semid, 1, GETVAL, sem_args));
    if(ret==-1)
    {
        perror("shmctl error:");
        exit(EXIT_FAILURE);
    }
    struct sembuf sem1_opt_wakeup[1]={0,1,SEM_UNDO};
    struct sembuf sem2_opt_wait[1]={1,-1,SEM_UNDO};
    while(1)
    {
        int i=0;
        //int semopt(int semid, struct sembuf *sops, unsigned nsops)
        //struct sembuf {
        //short semnum; //信号量集合中信号的编号，0代表第一个信号量
        //short val; //如果信号量值val大于0也就是v操作，若val小于o就是p操作。最终信号量的值semval = semval - val
        //short flag;//设置信号量的默认操作。IPC_NOWAIT设置信号量操作默认不等待，SEM_UNDO让内核记录一个与调用进程相关的UNDO记录，如果该进程崩溃，根据这个进程的UNDO记录自动恢复相应信号量的计数值
        //};
        //nsops操作信号量的个数，也就是sops结构中的变量个数
        semop(semid,sem2_opt_wait,1);
        //void *shmat(int shmid, const void *addr, int flag);
        // shmid:共享存储的id
        // addr: 一般为0，表示连接到由内核选择的第一个可用地址上，否则，如果flag没有指定SHM_RND，则连接到addr所指定的地址上，如果flag为SHM_RND，的地址取整
        addr=(int *)shmat(shmid,NULL,0);
        printf("please input your infornation:\n");
        scanf("%d%d",addr,addr+1);
        shmdt(addr);
        semop(semid,sem1_opt_wakeup,1);
        //printf("退出清输入1\n");
        //scanf("%d",&i);
        if(i==1)
        {
            shmctl(shmid,IPC_RMID,NULL);
            semctl(semid,1,IPC_RMID,NULL);
            semctl(semid,0,IPC_RMID,NULL);
            exit(1);
        }
    }
    return 0;
}
