/*********
execlp函数的用法
**********/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc<2){
		printf("vi的等效用法: %s filesname\n",argv[0]);
		return 1;
	}
	execlp("vim", "vim", argv[1], (char *)0);
	return 0;

}