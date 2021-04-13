//========================================
//*author:LiaoHuanxuan
//*create time :2021-03-31 02:42
//========================================
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MSGKEY 1234

struct msgbuf
{
	long mtype;     /* message type, must be > 0 */
	char mtext[100];  /* message data */
};

int main()
{
	int msgid;
	int ret;
	struct msgbuf mbuf;
	pid_t pid;

	msgid = msgget(MSGKEY, IPC_CREAT | IPC_EXCL);	//创建消息队列
	if (msgid == -1)
	{
		perror("msgget");
		exit(1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)		//子进程发送数据
	{
		while (1)
		{
			memset(mbuf.mtext, 0, sizeof(mbuf.mtext));
			scanf("%s", mbuf.mtext);
			mbuf.mtype = 1;

			ret = msgsnd(msgid, &mbuf, sizeof(mbuf.mtext), 0);
			if (ret == -1)
			{
				perror("msgsnd");
				exit(1);
			}

			if (!strcmp(mbuf.mtext, "0"))
			{
				mbuf.mtype = 2;
				msgsnd(msgid, &mbuf, sizeof(mbuf.mtext), 0);
				break;
			}
		}
	}
	else		//父进程接收数据
	{
		while (1)
		{
			memset(mbuf.mtext, 0, sizeof(mbuf.mtext));

			ret = msgrcv(msgid, &mbuf, sizeof(mbuf.mtext), 1,0);
			if (ret == -1)
			{
				perror("msgrcv");
				exit(1);
			}

			if (!strcmp(mbuf.mtext, "0"))
			{
				printf("exit\n");
				kill(pid, 2);
				break;
			}
			printf("get msg : %s\n", mbuf.mtext);
		}
	}
	sleep(1);
	msgctl(msgid, IPC_RMID, NULL);//销毁消息队列
	return 0;
}
