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
	int written;//��־������ɶ������д
	char text[TEXT_SZ];//��¼��ȡ��д�������
};

union semun  
{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry;  
}; 

static int sem_id = 0;  //�ź�����ʶ��


static int  get_sem(int projid,int size)
{
	//���������ź���
	sem_id = semget((key_t)projid, size, 0666 | IPC_CREAT);  
	if(sem_id == -1){  
    	fprintf(stderr, "Failed to delete semaphore\n");
		return -1;
	}
	return sem_id;
}

static int set_semvalue()  
{  
    //���ڳ�ʼ���ź�������ʹ���ź���ǰ����������  
    union semun sem_union;  
  
    sem_union.val = 1;  
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)  
        return 0;  
    return 1;  
}  
  
static void del_semvalue()  
{  
    //ɾ���ź���  
    union semun sem_union;  
  
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)  
        fprintf(stderr, "Failed to delete semaphore\n"); 
	else
		fprintf(stderr, "sucess to delete semaphore\n"); 
}  
  
static int semaphore_p()  
{  
    //���ź�������1���������ȴ�P��sv��  
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
    //����һ���ͷŲ�������ʹ�ź�����Ϊ���ã��������ź�V��sv��  
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
