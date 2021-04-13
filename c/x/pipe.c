//========================================
//*author:LiaoHuanxuan
//*create time :2021-03-29 22:06
//========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
void ReadPipe(int fd);
void WritePipe(int fd);
int main(int argc, char *argv[]){
	pid_t pid;
	int fd[2];
	int ret;

	ret = pipe(fd);//创建管道
	if(ret == -1){
		perror("pipe\n");
		exit(1);
	}

	pid = fork();//创建进程
	if(pid == -1){
		printf("fork error\n");
		return -1;
	}
	if(pid == 0){
		close(fd[1]);
		ReadPipe(fd[0]);
	}
	if(pid > 0){
		close(fd[0]);
		WritePipe(fd[1]);
		int a;
		wait(&a);
	}
	return 0;
}
void ReadPipe(int fd){
	int ret;
	char buf[32];

	while(1){
		memset(buf,0,sizeof(buf));
		ret = read(fd,buf,sizeof(buf));
		if(ret == -1){
			perror("read\n");
			exit(1);
		}
		if(!strcmp(buf,"0")){
			printf("exit\n");
			break;
		}
		printf("read from pipe:%s\n",buf);
	}
	close(fd);//关闭管道
}
void WritePipe(int fd){
	int ret;
	char buf[32];

	while(1){
		memset(buf,0,sizeof(buf));
		scanf("%s",buf);
		ret = write(fd,buf,sizeof(buf));
		if(ret == -1){
			perror("write\n");
			exit(1);
		}
		if(!strcmp(buf,"0"))
			break;
	}
	close(fd);
}
