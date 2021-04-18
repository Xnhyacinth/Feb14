#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

int main(int argc,char argv[]){
    pid_t pid;
    pid = fork();
	pthread_attr attr1;
    if(pid == -1){
        perror("fork error!\n");
        exit(1);
    }
    if(pid == 0){

    }
    if(pid > 0){
        
    }
    return 0;
}
