/***************8
   #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *status);

       pid_t waitpid(pid_t pid, int *status, int options);

       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

*************/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//定义功能函数，通过返回状态，判断进程是正常退出还是信号导致退出
void exit_s(int status){
	if(WIFEXITED(status))
		printf("nomal exit, status=%d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("signal exit!status=%d\n",WTERMSIG(status));
}

int main(void){
	pid_t pid, pid1;
	int status;

	if((pid=fork())<0){
		printf("child process error!\n");
		exit(0);
	}
	else if(pid == 0)//子进程
	{
		printf("in the child process!\n");
		exit(2); //调用exit函数正常退出
	}
	if(wait(&status)!=pid){//在父进程中调用wait函数等待子进程结束
		printf("this is a parent process!\n wait error!\n");
		exit(0);
	}
	exit_s(status);//wait函数调用成功，调用自定义的函数功能，判断退出类型。


	if((pid=fork())<0)//再创建一个子进程
	{
		printf("child process error!\n");
		exit(0);	
	}
	else if(pid == 0){
		printf("in the child process!\n");
		pid1 = getpid();
		//使用kill函数发送信号
		//kill(pid1,9);//结束进程
		kill(pid1,17);//进入父进程
		//kill(pid1,19);//终止进程
	}
	if(wait(&status)!=pid){
		printf("this is a parent process!\n wait error!\n");
		exit(0);
	}
	exit_s(status);
	exit(0);
}

/**************
kill(pid1,19)
# gcc -o wait_process  wait_process.c 
# ls
wait_process  wait_process.c
# ./wait_process 
in the child process!
nomal exit, status=2
in the child process!//这里就卡住了

kill(pid1,9)
# ./wait_process 
in the child process!
nomal exit, status=2
in the child process!
signal exit!status=9

kill(pid1,17)
# ./wait_process 
in the child process!
nomal exit, status=2
in the child process!
this is a parent process!
 wait error!
nomal exit, status=0
*************/