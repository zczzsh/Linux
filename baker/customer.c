#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "seml.h"

void *customer(void *arg)
{
    int number=(int)arg;
    printf("新顾客光临，拿号 %d 。 \n",number+1);
    int sid=sem_create();  //创建信号量
    v_customer(sid)  ;   // 顾客等待的人数加1
    p_server(sid);  //  如果此时有服务员空闲，则空闲服务员减1，没有空闲则阻塞
    printf("有服务员空闲，为顾客 %d 服务 。\n",number+1);
    sleep(3);  // 正在服务中
    printf("顾客 %d 已经离开。 \n",number+1);
    v_server(sid);   // 服务员服务完成，空闲人数加1
}

int main()
{
    pthread_t customers[20];
    for(int i=0;i<20;i++)   // 有20个顾客
    {
        pthread_create(&customers[i], NULL, customer, (void *)i);
        sleep(2);
    }

    for(int j=0;j<20;j++)
    {
        pthread_join(customers[j], NULL);
    }

    return 0;
 
}
