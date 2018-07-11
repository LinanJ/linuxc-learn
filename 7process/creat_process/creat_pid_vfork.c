/******
创建进程的几种方法
2. vfork()函数 需要引用<sys/types.h>和<unistd.h>这两个头文件
	vfork子进程不复制父进程的资源，而是和父进程共享地址空间。
	所以子进程中改了一个变量的值，父进程中这个值同样会被修改。
	vfork函数创建进程时，要使用_exit()退出子进程，不能使用exit()退出。

*****/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int gvar = 2;//全局变量

int main(void){
	pid_t pid;//进程号
	int var = 5;//局部变量

	printf("process id :%ld\n",(long)getpid());//getpid()获取当前的进程号?
	printf("gvar=%d, var=%d\n",gvar,var);

	if((pid=vfork())<0)
	{
		perror("error!\n");
		return 1;//为什么这里要return 1，而不是用exit()？
	}
	else if(pid == 0){//子进程
		gvar ++;
		var --;
		printf("in the child process: %ld, gvar=%d, var=%d\n",(long)getpid(),gvar,var);
		_exit(0);//退出子进程
	}
	else//父进程中
	{
		printf("in the parent process: %ld, gvar=%d, var=%d\n",(long)getpid(),gvar,var);
		return 0;
	}
	printf("test!\n");
}

/*************8888
# gcc -g -o vfork creat_pid_vfork.c 
# ls
creat pid.c  creat_pid_fork.c  creat_pid_vfork.c  fork  vfork
# ./vfork 
process id :4654
gvar=2, var=5
in the child process: 4655, gvar=3, var=4
in the parent process: 4654, gvar=3, var=4

这里面为什么也会调用一次，执行2次呢？
最开始是在父进程中，然后进入子进程，然后又回到父进程
和fork不同的是，vfork父子进程是空间共享的。可以看出，无论是全局变量还是局部变量，子进程中改变后，父进程中也跟着改变了。
***************/