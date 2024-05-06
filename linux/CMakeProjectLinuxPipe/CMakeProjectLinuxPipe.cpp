// CMakeProjectLinuxPipe.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxPipe.h"

#include <unistd.h>  
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <sys/wait.h>  

void sys_err(const char* str)
{
	perror(str);
	exit(1);
}


int main2(void)
{
	int fds[2];
	if (pipe(fds) == -1) {
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		close(fds[0]);//×Ó½ø³Ì¹Ø±Õ¶Á¶Ë
		sleep(10);
		write(fds[1], "hello", 5);
		exit(EXIT_SUCCESS);
	}

	close(fds[1]);//¸¸½ø³Ì¹Ø±ÕÐ´¶Ë
	char buf[10] = { 0 };
	read(fds[0], buf, 10);
	printf("receive datas = %s\n", buf);
	return 0;
}

int main1(void)
{
	pid_t pid;
	char buf[1024];
	int fd[2];
	char p[] = "test for pipe\n";

	if (pipe(fd) == -1)
		sys_err("pipe");

	pid = fork();
	if (pid < 0) {
		sys_err("fork err");
	}
	else if (pid == 0) {
		close(fd[1]);
		printf("child process wait to read:\n");
		int len = read(fd[0], buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);
		close(fd[0]);
	}
	else {
		close(fd[0]);
		write(fd[1], p, strlen(p));
		wait(NULL);
		close(fd[1]);
	}
	return 0;
}

int main(void)
{
	main2();

	return 0;
}