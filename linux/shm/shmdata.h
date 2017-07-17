#ifndef _SHMDATA_H
#define _SHMDATA_H
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/sem.h>  

#define TEXT_SZ 2048
#define USE_ST 0x1223
struct shared_use_st{
	int written;//标志，非零可读，零可写
	char text[TEXT_SZ];//记录读取和写入的数据
};

union semun  
{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry;  
}; 

static int sem_id = 0;  //信号量标识符


static int  get_sem(int projid,int size)
{
	//用于申请信号量
	sem_id = semget((key_t)projid, size, 0666 | IPC_CREAT);  
	if(sem_id == -1){  
    	fprintf(stderr, "Failed to delete semaphore\n");
		return -1;
	}
	return sem_id;
}

static int set_semvalue()  
{  
    //用于初始化信号量，在使用信号量前必须这样做  
    union semun sem_union;  
  
    sem_union.val = 1;  
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)  
        return 0;  
    return 1;  
}  
  
static void del_semvalue()  
{  
    //删除信号量  
    union semun sem_union;  
  
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)  
        fprintf(stderr, "Failed to delete semaphore\n"); 
	else
		fprintf(stderr, "sucess to delete semaphore\n"); 
}  
  
static int semaphore_p()  
{  
    //对信号量做减1操作，即等待P（sv）  
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = -1;//P()  
    sem_b.sem_flg = SEM_UNDO;  
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_p failed\n");  
        return -1;  
    }  
    return 1;  
}  
  
static int semaphore_v()  
{  
    //这是一个释放操作，它使信号量变为可用，即发送信号V（sv）  
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = 1;//V()  
    sem_b.sem_flg = SEM_UNDO;  
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_v failed\n");  
        return -1;  
    }  
    return 1;  
}

#endif
