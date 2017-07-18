#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"
int main(int argc, char *argv[]){
	int running = 1;//�����Ƿ�������еı�־  
    void *shm = NULL;//����Ĺ����ڴ��ԭʼ�׵�ַ  
    struct shared_use_st *shared;//ָ��shm  
    int shmid;//�����ڴ��ʶ��  
    int pan = 0;
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
        //�����һ�α����ã���ʼ���ź���  
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
    //��һ��������shm_id����shmget�������صĹ����ڴ��ʶ��
	//�ڶ���������shm_addrָ�������ڴ����ӵ���ǰ�����еĵ�ַλ�ã�ͨ��Ϊ�գ���ʾ��ϵͳ��ѡ�����ڴ�ĵ�ַ��
	//������������shm_flg��һ���־λ��ͨ��Ϊ0��
    shm = shmat(shmid, 0, 0);  
    if(shm == (void*)-1) //�˴�void*�Ƕ�-1��һ������ת�� 
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    printf("\nMemory attached at %X\n", (int)shm);  
    //���ù����ڴ�  
    shared = (struct shared_use_st*)shm;  
    shared->written = 0;  
    while(running)//��ȡ�����ڴ��е�����  
    {  
        //û�н��������ڴ涨���������ݿɶ�ȡ
        #if 0
        if(shared->written != 0)
		#else
		if(semaphore_p())
		#endif
        {  	
        	//sleep(1);
            printf("You wrote: %s,no=%d\n", shared->text,pan++);  
            //sleep(rand() % 2);  
            //��ȡ�����ݣ�����writtenʹ�����ڴ�ο�д  
			semaphore_v();
			//sleep(2);
            //������end���˳�ѭ��������  
            if(strncmp(shared->text, "end", 3) == 0)  
                running = 0;  
        }  
        else
			{//������������д���ݣ����ܶ�ȡ����  
            sleep(1);
			 printf("Waiting...\n"); 
        }
    } 
	
    //�ѹ����ڴ�ӵ�ǰ�����з���  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //ɾ�������ڴ�  
    if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  

	if(argc > 1)  
    {  
        //��������ǵ�һ�α����ã������˳�ǰɾ���ź���  
        sleep(3);  
        del_semvalue();  
    } 
    exit(EXIT_SUCCESS);  
	return 0;
}
