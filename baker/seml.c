#include "seml.h"

int sem_create()   //信号量创建
{
     int key = ftok(".", 1);            // 当前目录下创建key
     return semget(key, 2, IPC_CREAT);  // 有两个key值，服务员空闲的人数和顾客等待的人数，参数为2.
}

int p_customer(int sid)        // 顾客等待的p操作，将等待人数减1
{
     struct sembuf operation = {0, -1, SEM_UNDO};     

     //short sem_num;//除非使用一组信号量，否则它为0 ,一组信号量，如本题两个，该值为0和1，代表高位和低位 
    //short sem_op;//信号量在一次操作中需要改变的数据，通常是两个数，一个是-1，即P（等待）操作，  
                    //一个是+1，即V（发送信号）操作。  
    //short sem_flg;//通常为SEM_UNDO,使操作系统跟踪信号，  
                    //并在进程没有释放该信号量而终止时，操作系统释放信号量  
 
     return semop(sid, &operation, 1);   // semop函数的作用是改变信号量的值，通过operation操作把sid信号量的值改变
}  

int v_customer(int sid)
{
     struct sembuf operation = {0, 1, SEM_UNDO};
     return semop(sid, &operation, 1);
}

int p_server(int sid)
{
     struct sembuf operation = {1, -1, SEM_UNDO};
     return semop(sid, &operation, 1);
}

int v_server(int sid)
{
     struct sembuf operation = {1, 1, SEM_UNDO};
     return semop(sid, &operation, 1);
}

