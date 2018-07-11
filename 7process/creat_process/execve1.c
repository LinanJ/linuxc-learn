/******
创建进程的几种方法
3. exec()函数族 
	使用if else让execve函数在子进程中执行，其余代码在父进程中执行

*****/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char* argv[]){
	pid_t pid;

	if((pid=fork())<0){//用fork函数创建进程
		puts("creat process failed!\n");
	}
	if(pid == 0){
		puts("在子进程中调用execve函数\n");
		execve("new",argv,environ);
	}
	else
		puts("父进程输出信息！\n");
}

/***********88
# gcc -o execve1 execve1.c 
# ls
creat pid.c       creat_pid_vfork.c  execve1    execve.c  new     vfork
creat_pid_fork.c  execve             execve1.c  fork      new2.c
# ./execve1 
父进程输出信息！

# 在子进程中调用execve函数

welcome to new!

这里是先执行了父进程然后在执行子进程
既然不同的系统，父子进程执行的顺序不同，这会不会为逻辑的实现带来困难?

***********8/