/*
Coen 177: Operating Systems Lab 1

Created By: Joseph phan

File Name: assignment1.c

File Description: This is a simple shell program that willterminate if the user enters “exit” 
at the command line. It will launch a  program in response to any other 
input string. The program that will be launched here is a simple “hello world”
program
			
		waitpid(pid_t pid, int *status, int options);
		< -1: Wait for any child process whose process group ID is equal to the absolute value of pid.
		-1: Wait for any child process.
		0: Wait for any child process whose process group ID is equal to that of the calling process.
		> 0: Wait for the child whose process ID is equal to the value of pid.

		execve(const char *filename, char *const argv[], char *const envp[]);


	TO TEST:
	Create a helloworld.c file with this code:

	#include <stdio.h>

	int main()
	{
	    printf("Hello World\n");
	    return 0;

	Compile it gcc -0 helloworld helloworld.c

	Compile this program, and when it prompts you for Enter Executable File Name:
	Type "helloworld" , or whatever executable of a program you want to run
}



*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main () {
	int status;

	while (1) {
		// Read the Command from the User
		char command_string[100];
		char *newargv[] = { NULL, "hello", "world", NULL };
    	char *newenviron[] = { NULL };


		printf("\nEnter Executable File Name: ");
		scanf("%s", command_string);

		// Check to exit
		if (strcmp(command_string,"exit") == 0) {
			exit(0);
		}

		// If it is a parent process, wait for child to die
		if (fork() != 0) {
			//Parent Process
			waitpid(-1, &status, 0);
		
		} else {
			//Child Process: Execute program
			execve (command_string, newargv, newenviron);
			//program executed: exit
			exit(0);
		}
	}

	return 0;
}
