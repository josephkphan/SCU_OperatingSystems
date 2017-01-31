/*
Coen 177: Operating Systems Lab 1

Created By: Joseph phan

File Name: assignment2.c

File Description: This program creates exactly eight child processes (including 
the initial program itself). No single process to create more than two child processes.

My Implementation: The Initial program will create one child process, and that process will create one
child process, until there are 8 total processes

      0	Initial process                1
      |
      0 Child                          1
      |
      0 grandchild                     1
      |
      0 grandgrandchild                1
      |
      0 G3 child                       1
      |
      0 ... you get the memo           1
      |
      0                                1
      |
      0                                1    Sum = 8

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define true 1
#define false 0

int main () {
	int i;
	int result;
	int status;
	int is_initial_process = true;
	for (i = 0; i < 7; i++) {
		result = fork();

		// Handle Error
		if (result == -1) {
			printf("Error Creating Child");
		}else if (result != 0) {
		// This is a parent process
			if(is_initial_process){
				printf("This is the initial process\n");
				printf("Initial Process PID: %d \n", getpid());
			}
			waitpid(-1, &status, 0);
			exit(0);
		} else {
		// This is a child process
			is_initial_process = false;
			printf("Created child process number: %d \n", i+1);
			printf("Child  PID: %d | Parent PID: %d \n", getpid(),getppid());
		}
		
	}
	printf("\nPrinting from last child\nTotal Processses : %d\n",i+1 );

	exit(0);

	return 0;
}
