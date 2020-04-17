#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t resource1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource3 = PTHREAD_MUTEX_INITIALIZER;

void* process1()
{
	pthread_mutex_lock(&resource1);
	printf("Resource 1 is locked by Process 1\n");
	sleep(1);
	printf("Resource 2 is requested by Process 1\n");
	pthread_mutex_lock(&resource2);
	printf("Resource 2 is locked by Process 1\n");
	sleep(2);
	pthread_mutex_unlock(&resource2);
	printf("Resource 2 is released by Process 1\n");
	pthread_mutex_unlock(&resource1);
	printf("Resource 1 is released by Process 1\n");
}

void* process2()
{
	pthread_mutex_lock(&resource2);
	printf("Resource 2 is locked by Process 2\n");
	sleep(1);
	printf("Resource 3 is requested by Process 2\n");
	pthread_mutex_lock(&resource3);
	printf("Resource 3 is locked by Process 2\n");
	sleep(2);
	pthread_mutex_unlock(&resource3);
	printf("Resource 3 is released by Process 2\n");
	pthread_mutex_unlock(&resource2);
	printf("Resource 2 is released by Process 2\n");
}

void* process3()
{
	pthread_mutex_lock(&resource3);
	printf("Resource 3 is locked by Process 3\n");
	sleep(1);
	printf("Resource 1 is requested by Process 3\n");
	pthread_mutex_lock(&resource1);
	printf("Resource 1 is locked by Process 3\n");
	sleep(2);
	pthread_mutex_unlock(&resource3);
	printf("Resource 1 is released by Process 3\n");
	pthread_mutex_unlock(&resource2);
	printf("Resource 3 is released by Process 3\n");
}

int main()
{
	pthread_t t1,t2,t3;
	pthread_create(&t1,NULL,process1,NULL);
	pthread_create(&t2,NULL,process2,NULL);
	pthread_create(&t3,NULL,process3,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
}
