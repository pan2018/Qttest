#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/shm.h>  
#include "shmdata.h"  
  
int main(int argc, char *argv[])  
{  
    int running = 1;  
    void *shm = NULL;  
    struct shared_use_st *shared = NULL;  
    char buffer[BUFSIZ + 1];//用于保存输入的文本  
    int shmid;  
    //创建共享内存  
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1)  
    {  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  
	//创建信号量
	sem_id = semget((key_t)1223, 1, 0666 | IPC_CREAT);  
	if(sem_id >0)
		printf("sem suceess \n");
	else
		printf("sem fail %s\n",stderr);
	if(argc > 1)  
    {  
        //程序第一次被调用，初始化信号量  当有参数时表明首先被调用
        if(!set_semvalue())  
        {  
            fprintf(stderr, "Failed to initialize semaphore\n");  
            exit(EXIT_FAILURE);  
        }  
		printf("hello\n");
        //设置要输出到屏幕中的信息，即其参数的第一个字符  
        //message = argv[1][0];  
        sleep(2);  
    }
	
    //将共享内存连接到当前进程的地址空间  
    shm = shmat(shmid, (void*)0, 0);  
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    printf("Memory attached at %X\n", (int)shm);  
    //设置共享内存  
    shared = (struct shared_use_st*)shm;  
    while(running)//向共享内存中写数据  
    {  
        //数据还没有被读取，则等待数据被读取,不能向共享内存中写入文本  
#if 0
		while(shared->written == 1)
#else
		sleep(2);  
		while(!semaphore_p())
#endif
        {  
           // sleep(1);  
            printf("Waiting...\n");  
        }  
		
        //向共享内存中写入数据  
        printf("Enter some text: ");  
        //fgets(buffer, BUFSIZ, stdin); 
		scanf("%s",buffer);
        strncpy(shared->text, buffer, TEXT_SZ);  
        //写完数据，设置written使共享内存段可读  
        //shared->written = 1;
		semaphore_v();
        //输入了end，退出循环（程序）  
        if(strncmp(buffer, "end", 3) == 0) { 
            running = 0;  
        	}
    }  
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    sleep(2);  
	if(argc > 1)  
    {  
        //如果程序是第一次被调用，则在退出前删除信号量  
        sleep(3);  
        del_semvalue();  
    } 
    exit(EXIT_SUCCESS);  
}

