#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int pipe1[2], pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	
	pid_t wcPid = fork();
	bool wcBool = false, gnetcatBool = false;
	if (wcPid == 0) {
		char start[] = "Starting wc:\n";
		write(2, start, strlen(start));
		dup2(pipe1[1], 1);
		close(pipe1[1]);
		dup2(pipe2[0], 0);
		close(pipe1[0]);
		close(pipe2[0]);
		close(pipe2[1]);
		
		wcBool = true;
		
		// exec()
		argv[2] = NULL;
		execvp(argv[1], argv + 1);
	}
	else if (wcPid > 0) {
		if (fork() == 0) {
			char start[] = "Starting gnetcat:\n";
			write(2, start, strlen(start));
			dup2(pipe1[0], 0);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe1[0]);
			dup2(pipe2[1], 1);
			close(pipe2[1]);
			
			gnetcatBool = true;
			
			// exec()
			execvp(argv[2], argv + 2);
		}
	}
	
	if (!wcBool && !gnetcatBool) {
		close(pipe1[1]);
		close(pipe2[1]);
		close(pipe1[0]);
		close(pipe2[0]);
		// wait()
		// wait()
		int waitStatus = 0;
		wait(&waitStatus);
		wait(&waitStatus);
	}
	
	return 0;
}
