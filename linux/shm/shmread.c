#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"
int main(int argc, char *argv[]){
	int running = 1;//程序是否继续运行的标志  
    void *shm = NULL;//分配的共享内存的原始首地址  
    struct shared_use_st *shared;//指向shm  
    int shmid;//共享内存标识符  
    int pan = 0;
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
        //程序第一次被调用，初始化信号量  
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
    //第一个参数，shm_id是由shmget函数返回的共享内存标识。
	//第二个参数，shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
	//第三个参数，shm_flg是一组标志位，通常为0。
    shm = shmat(shmid, 0, 0);  
    if(shm == (void*)-1) //此处void*是对-1的一个类型转换 
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    printf("\nMemory attached at %X\n", (int)shm);  
    //设置共享内存  
    shared = (struct shared_use_st*)shm;  
    shared->written = 0;  
    while(running)//读取共享内存中的数据  
    {  
        //没有进程向共享内存定数据有数据可读取
        #if 0
        if(shared->written != 0)
		#else
		if(semaphore_p())
		#endif
        {  	
        	//sleep(1);
            printf("You wrote: %s,no=%d\n", shared->text,pan++);  
            //sleep(rand() % 2);  
            //读取完数据，设置written使共享内存段可写  
			semaphore_v();
			//sleep(2);
            //输入了end，退出循环（程序）  
            if(strncmp(shared->text, "end", 3) == 0)  
                running = 0;  
        }  
        else
			{//有其他进程在写数据，不能读取数据  
            sleep(1);
			 printf("Waiting...\n"); 
        }
    } 
	
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //删除共享内存  
    if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  

	if(argc > 1)  
    {  
        //如果程序是第一次被调用，则在退出前删除信号量  
        sleep(3);  
        del_semvalue();  
    } 
    exit(EXIT_SUCCESS);  
	return 0;
}
