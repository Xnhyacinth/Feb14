/* sigex----------shows how sigaction works */
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
 
int main(void)
{
    static struct sigaction act;//设置为静态变量，使得系统把结构的各个成员初始化为零
 
    /*declare catchint,later to be use as the handler */
    void catchint(int);//信号处理函数
 
    /*set up the action to be taken on receipt of SIGINT */
    act.sa_handler=catchint;
 
    /* create a full mask */
    sigfillset(&(act.sa_mask));//设置所有的信号，意味着阻塞所有的信号，除了signo参数的信号
    
    /* before sigaction call,SIGINT will 
     * terminate process (default action) */
 
 
 
 
//未调用信号处理函数之前
    printf("no sigaction call:#1\n");
   sleep(1);
    printf("no sigaction call:#2\n");
    sleep(1);
    printf("no sigaction call:#3\n");
  sleep(1);
 
    printf("no sigaction call:#4\n");
    sleep(1);
    printf("use sigaction call\n");
 
 
//调用信号处理函数
    sigaction(SIGINT,&act,NULL);
 
    /*on receipt of SIGINT control will be passed
     * to catchint
     */
 
    printf("sleep call #1\n");
    sleep(1);
    printf("sleep call #2\n");
    sleep(1);
    printf("sleep call #3\n");
    sleep(1);
    printf("sleep call #4\n");
    sleep(1);
 
    printf("Exiting...\n");
    exit(0);
}
 
/*trivial function to handler SIGINT */
 
void catchint(int signo)
{
    printf("\nCATCHINT:signo=%d\n",signo);
 
    printf("CATCHINT :returning \n\n");
}