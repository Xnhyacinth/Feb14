//========================================
//*author: Xnhyacinth
//*create time :2021-03-21 15:21
//*filename:kill.c
//========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	int sig;
	int pid;
	if(argc < 3){
		printf("please input param\n");
		return -1;
	}
	sig = atoi(argv[1]);
	pid = atoi(argv[2]);
	kill(pid,sig);
	return 0;
}
