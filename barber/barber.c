#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
#include <math.h>


int chairs_num=4;   // 总共4把椅子
int waiting=0;  // 等待的人数
sem_t barbers;   // 理发师信号量
sem_t customers;  // 顾客信号量

sem_t chairs;  // 互斥信号量，此时是椅子的数目


void *barber(void *arg)
{
     
      while (1)
      {
          sem_wait(&customers);   // 访问顾客数量，如果此时有顾客，顾客数量减1，否则阻塞
          sem_wait(&chairs) ; // 访问互斥量，上锁
          waiting=waiting-1;        // 等待人数减1    
          printf("理发师给顾客理发. \n");
          sleep(3);
          sem_post(&chairs);  
          sem_post(&barbers);  // 理发师结束理发，空闲               
      }
}


void *customer(void *arg)
{
      sem_wait(&chairs) ; //顾客来时，先访问互斥量，看是否有等待的位置
      if(waiting<chairs_num)        // 还有空余位置
      {
           waiting++;                // 等待人数加1
           printf("顾客 %d 等待理发.\n", (int)(arg+1));
           sem_post(&chairs);    // 解锁
	   sem_post(&customers);    // 顾客人数加1
           sem_wait(&barbers);        
      }
      else
      {
           printf("顾客 %d 离开.\n", (int)(arg+1));
           sem_post(&chairs);    // 解锁
      }
}


int main()
{

      sem_init(&chairs, 0, 1);  //互斥信号量初始化1
      sem_init(&customers, 0, 0);//顾客信号量初始化0
      sem_init(&barbers, 0, 1);//理发师信号量初始化1

      pthread_t customers[20], barbers;
      pthread_create(&barbers, NULL, barber, NULL);
      for(int i=0;i<20;i++)   
      {
           pthread_create(&customers[i], NULL, customer, (void *)i);
      }
      for(int j=0;j<20;j++)
      {
           pthread_join(customers[j], NULL);
      } 
      pthread_join(barbers,NULL);

      system("pause");
      return 0;
}
