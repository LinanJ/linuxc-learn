#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
	int a;
	pid_t pgid, pid;//进程组ID，和进程ID
	pid = (long)getpid();//获取当前的程序的进程id
	pgid = (long)getpgrp();//获取当前的进程组id
	a = setpgid(pid, pgid);//把他们放到一个进程组里
	printf("a=%d, pid=%d,pgid=%d\n",a,pid,pgid);
	return 0;
}