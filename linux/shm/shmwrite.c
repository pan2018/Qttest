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
    char buffer[BUFSIZ + 1];//���ڱ���������ı�  
    int shmid;  
    //���������ڴ�  
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1)  
    {  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  
	//�����ź���
	sem_id = semget((key_t)1223, 1, 0666 | IPC_CREAT);  
	if(sem_id >0)
		printf("sem suceess \n");
	else
		printf("sem fail %s\n",stderr);
	if(argc > 1)  
    {  
        //�����һ�α����ã���ʼ���ź���  ���в���ʱ�������ȱ�����
        if(!set_semvalue())  
        {  
            fprintf(stderr, "Failed to initialize semaphore\n");  
            exit(EXIT_FAILURE);  
        }  
		printf("hello\n");
        //����Ҫ�������Ļ�е���Ϣ����������ĵ�һ���ַ�  
        //message = argv[1][0];  
        sleep(2);  
    }
	
    //�������ڴ����ӵ���ǰ���̵ĵ�ַ�ռ�  
    shm = shmat(shmid, (void*)0, 0);  
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    printf("Memory attached at %X\n", (int)shm);  
    //���ù����ڴ�  
    shared = (struct shared_use_st*)shm;  
    while(running)//�����ڴ���д����  
    {  
        //���ݻ�û�б���ȡ����ȴ����ݱ���ȡ,���������ڴ���д���ı�  
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
		
        //�����ڴ���д������  
        printf("Enter some text: ");  
        //fgets(buffer, BUFSIZ, stdin); 
		scanf("%s",buffer);
        strncpy(shared->text, buffer, TEXT_SZ);  
        //д�����ݣ�����writtenʹ�����ڴ�οɶ�  
        //shared->written = 1;
		semaphore_v();
        //������end���˳�ѭ��������  
        if(strncmp(buffer, "end", 3) == 0) { 
            running = 0;  
        	}
    }  
    //�ѹ����ڴ�ӵ�ǰ�����з���  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    sleep(2);  
	if(argc > 1)  
    {  
        //��������ǵ�һ�α����ã������˳�ǰɾ���ź���  
        sleep(3);  
        del_semvalue();  
    } 
    exit(EXIT_SUCCESS);  
}

