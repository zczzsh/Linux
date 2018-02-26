#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "seml.h"

void *server(void *arg)
{
    int sid=sem_create();  //创建信号量
    v_server(sid);          // 每次有新的线程建立时，将服务员空闲的人数加1
    while(1)
    {
        int number=(int)arg;
        p_customer(sid);   // 顾客等待的人数减1,不能减的时候阻塞
        printf("服务员 %d :有客户等待，开始服务 。 \n",number+1);
        sleep(3);  //  正在服务中
    }
}

int main()
{
    pthread_t servers[3];
    for(int i=0;i<3;i++)   // 有三个服务员
    {
        pthread_create(&servers[i], NULL, server, (void *)i);
    }

    for(int j=0;j<3;j++)
    {
        pthread_join(servers[j], NULL);
    }

    return 0;
 
}
