/******
创建进程的几种方法
1. fork()函数 需要引用<sys/types.h>和<unistd.h>这两个头文件
	返回值类型为pid_t，一个非负的整数。
	如果程序在父进程中返回的是，子进程的进程号
	如果在子进程中，返回的是0
	如果调用fork函数创建失败，返回-1.(两种失败的原因 EAGAIN ENOMEM)

*****/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int gvar = 2;

int main(void){
	pid_t pid;//进程号
	int var = 5;
	if((pid = fork())<0){//用fork函数创建进程
		printf("fork error!\n");
		exit(1);
	}
	else if(pid == 0) //在子进程中
	{
		gvar ++;
		var --;
		printf("in the child process:%ld, gvar=%d, var=%d\n",(long)getpid(),gvar,var);
	}
	else
		printf("in the parent process:%ld, gvar=%d, var=%d\n",(long)getpid(),gvar,var);//在父进程中
	printf("pid %d!\n",pid);
	exit(0);
}

/*************
# gcc -g -o fork creat_pid.c 
# ls
creat pid.c  creat_pid.c  fork
# ./fork 
in the parent process!
pid 4557
# in the child process!
pid 0

为什么输出了2次pid呢？

fork函数：调用1次，返回2次。
父进程返回一次，子进程返回一次。
子进程是通过复制父进程得到的，所以子进程和父进程的进程环境，内存资源是一样的。
父子的调用顺序不同的内核调用算法不同。
可以通过fork函数，在父子进程内写不同的代码输出。

增加了全局变量和局部变量的改动后，和vfork函数做对比。
很奇怪的是，这里父进程好像是执行结束了，然后又调用的子进程。

# ./fork 
in the parent process:4713, gvar=2, var=5
# in the child process:4714, gvar=3, var=4
****************/