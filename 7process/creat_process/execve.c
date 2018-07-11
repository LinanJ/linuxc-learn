/******
创建进程的几种方法
3. exec()函数族 
	需要引用<sys/types.h>和<unistd.h>这两个头文件，而且必须预定义全局变量extern char **environ
	exec函数族的函数都实现了对子进程中的数据段，代码段，堆栈段进行替换的功能
	执行成功，没有返回值
	执行失败，返回-1.
exec函数族中：
	名字带p的path，只需写出文件名，不用写路径，他会自动搜索路径。
	名字带l的list，表示要将新程序的每个命令行参数输进去，参数个数是可变的，用最后一个参数是NULL代表结束。
	名字带v的vector，支持参数数组，类似于main的argv[]，最后一个参数也要是NULL.
	名字以e结尾，表示可以将一份新的环境变量表传给它。
	execve()是其他函数的基础，其他函数在执行时，都要在最后调用一次execve()。这个函数是系统调用的。

*****/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char* argv[]){
	execve("new",argv,environ);
	puts("正常情况下无法输出此信息！\n");
}

/*********88
# gcc -o execve execve.c 
# gcc -o new new2.c 
# ./execve 
welcome to new!

*************/