//========================================
//*author: Xnhyacinth
//*create time :2021-04-03 15:50
//*filename:jump.c
//========================================
#include  <stdio.h>
#include  <stdlib.h>
#include  <setjmp.h>
jmp_buf buf;
 
void banana()
{ 
    printf("in banana() \n"); 
    longjmp(buf,2);
    printf("you'll never see this,because i longjmp'd");
 
}
 
int main() 
{ 
	int rvalu;
	rvalu = setjmp(buf);
    if(rvalu) 
    {
        printf("back in main\n"); 
        printf("return value is %d\n", rvalu); //输出值为，longjmp的第二个参数的值，可根据这个值，判断发生异常的事情
	}
    else
    { 
        printf("first time through\n"); 
        banana(); 
    }
 
}
