#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "add.h"
#include "minus.h"
#include "multiply.h"
int main(int argc,char argv[]){
    int a = 3;
    int b = 5;
    printf("%d + %d = %d\n",a,b,add(3,5));//静态库链接
    printf("%d - %d = %d\n",a,b,minus(3,5));//动态库链接

    void *handle = NULL;
	typedef int (*p)(int,int);
	char *error = NULL;
	
	/* 打开动态链接库 */
	handle = dlopen("./libmultiply.so",RTLD_LAZY); 
	/* 动态库错误函数 */
	if((error = dlerror()) != NULL)
	{
		printf("%s\n",error);
		exit(1);	
	}
	/* 取函数(test_fun)执行地址 */
	p mul = (p)dlsym(handle,"multiply");
	if((error = dlerror()) != NULL)
	{
		printf("%s\n",error);
		dlclose(handle);
		exit(1);	
	}
    printf("%d * %d = %d\n",a,b,mul(a,b));
	dlclose(handle);
	return 0;
}