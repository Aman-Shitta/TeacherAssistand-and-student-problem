#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
sem_t s;
pthread_mutex_t m;
pthread_mutex_t m1;
struct std
{
	int studentID[3];
	int time[3];
};
struct TA_teacher
{
	int state;
}ptr2;
void mainfunc();
void *working1(void *args2);
void *sleep11(void *args1);
void *sleeping(void *args3);

void *check(void *args)
{
	pthread_t slept;
	int i;
	pthread_mutex_lock(&m);
	struct std *ptr1=args;
	for(i=0;i<3;i++)
	{
		if(ptr1->studentID[i]!=0)
		{
			ptr2.state=1;
			break;	
		}
		if(ptr1->studentID[0]==ptr1->studentID[1]==ptr1->studentID[2]==0)
		{
			ptr2.state=0;
			goto j2;
		}
	}
	j2:	
		pthread_create(&slept,NULL,sleep11 ,NULL);
		pthread_join(slept,NULL);
	pthread_mutex_unlock(&m);
//	return 0;
}
void *sleep11(void *args1)
{
    	ptr2.state=0;
}
void *sleeping(void *args3)
{
	int i,a;
	printf("Enter 1 for new std:\n");
	printf("\nTA Sleeping: \n");
	pthread_mutex_lock(&m1);
	for(i=0;i<100;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			goto j3;
		}
		sleep(i-(i-2));
	}
	j3:
		main();
	pthread_mutex_unlock(&m1);
	
}
void *working1(void *args2)
{
	int i,sum;
	//int a;
	pthread_t slept12;
	struct std *ptr1=args2;
	ptr2.state=1;
	sem_wait(&s);
		printf("To Continue Press 0 and to go back Press1:\n");
		for(i=0;i<3;i++)
		{
			if(ptr1->studentID[i]!=0)
			{
			printf("TA Teaching -->Stdudent ID :%d  for  %d seconds...\n",ptr1->studentID[i],ptr1->time[i]);
			sleep(ptr1->time[i]);
			//scanf("%d",&a);
			//if(a==1)
			//{
				//mainfunc();
			//}
			}
		}
		
	sem_post(&s);
		pthread_create(&slept12,NULL,sleeping ,NULL);
		pthread_join(slept12,NULL);
		
		
}
int main()
{
	int queue[3]={0,0,0},i,loop=0,var,time1=0,temp=0,remove;
	pthread_t rq,work;
	sem_init(&s,1,1);
	struct std ptr1;
	//struct TA_teacher ptr2;
	for(i=0;i<3;i++)
	{
		ptr1.studentID[i]=0;
		ptr1.time[i]=0;
	}

	void mainfunc()
	{
	
	while(loop==0)
	{
	printf("\nPlease ENTER The Following choices:\n");
	printf("1. ADD a new std\n");
	printf("2. REMOVE an old std\n");
	printf("3. DISPLAY current scenario\n");
	printf("4. EXIT\n");
	scanf("%d",&var);
	switch(var)
	{
		case 1:
			printf("\nEnter the ID of std\n");
			scanf("%d",&temp);
			printf("Enter the time taken by std in seconds\n");
			scanf("%d",&time1);
			for(i=0;i<3;i++)
			{
				if(queue[i]!=1)
				{
					queue[i]=1;
					goto j1;
				}
				else
				{
					printf("Chair %d id occupied\n",i);
				}
			}
			printf("\nSORRY WAIT FOR SOME TIME\n");
			break;
			j1:
			printf("\nThanks for your entry\n");
			ptr1.studentID[i]=temp;
			ptr1.time[i]=time1;
			pthread_create(&rq,NULL,check ,&ptr1);
			pthread_join(rq,NULL);
			break;
		case 2:
			printf("\nstd ID with Time:\n");
			for(i=0;i<3;i++)
			{
				printf("%d. Id:%d ->Time:%d\n",i,ptr1.studentID[i],ptr1.time[i]);
			}
			printf("\nEnter the ID of std to be removed:\n");
			scanf("%d",&remove);
			for(i=0;i<3;i++)
			{
				if(ptr1.studentID[i]==remove)
				{
					ptr1.studentID[i]=0;
					ptr1.time[i]=0;
					queue[i]=0;
				}
			}
			pthread_create(&rq,NULL,check ,&ptr1);
			pthread_join(rq,NULL);
			break;
		case 3:
			printf("\nSCENARIO\n");
			for(i=0;i<3;i++)
			{
				printf("ID: %d  Time: %d\n",ptr1.studentID[i],ptr1.time[i]);
			}
			pthread_create(&work,NULL,working1 ,&ptr1);
			pthread_join(work,NULL);
			break;
		case 4:
			loop=1;
			exit;
	}
	}
	}
	mainfunc();
}

