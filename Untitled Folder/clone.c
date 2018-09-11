#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>

//use this guy to pick a name for our log
uint32_t logId;
pthread_mutex_t idLock;


FILE * createLog(uint32_t logId)
{
    char id[20];
    char name[30];
    strcpy(name, "log");
    //id will now hold a string equal to t
    sprintf(id,"%d", logId);
    //name is log, add whatever logId is to it, now we get something like log34, etc
    strcat(name,id);
    
    FILE *logfile = fopen(name,"wb");
}

void* doSomeThing(void *arg)
{
    pthread_mutex_lock(&idLock);
    uint32_t t = logId++;
    pthread_mutex_unlock(&idLock);
    
    FILE *log = createLog(t);

   	fwrite(arg, sizeof(uint32_t)*500, 1, log);

    fclose(log);
    		
    printf("arg %d \n",*(int*)arg);
    
    
    system("python pu");
    
    //free(arg);

    return NULL;
}

int main(void)
{
    int i = 69;
    int err;
    
    int * ptr = malloc(500);
    int *ptrIter = ptr;
    
    int counter =0;
    for(counter =0 ; counter < 500; counter++)
    {
        *ptrIter++ = counter;
    }
    
  
    printf("%d \n", ptr[5]);
    
    pthread_t tid;
       
    pthread_create(&tid, NULL, &doSomeThing, ptr);
    pthread_create(&tid, NULL, &doSomeThing, ptr);
    pthread_create(&tid, NULL, &doSomeThing, ptr);
    pthread_create(&tid, NULL, &doSomeThing, ptr);
    sleep(5);
    return 0;
}

int main2()
{
    char s[11]; 
    sprintf(s,"%d", 1000);
    //printf("%s \n",s);
    
    char *ptr = s;
    while(*ptr != '\0'){
        printf("%c \n", *ptr);
        *ptr++;
        }

}

