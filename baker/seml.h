#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/sem.h>


union semun  
{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry; 
    struct seminfo *__buf; 
}; 

int sem_create() ;
int p_customer(int sid);
int v_customer(int sid);
int p_server(int sid);
int v_server(int sid);
