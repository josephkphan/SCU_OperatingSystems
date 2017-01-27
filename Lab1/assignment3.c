
/*
Coen 177: Operating Systems Lab 1

Created By: Joseph phan

File Name: assignment3.c

File Description This Program when launched, will result in a total of twelve child processes to run. 
any single process which  creates children creates at least two child processes, but no more than three.
In other words There is maximum of three child processes directly, and any other “children” will have to be 
created by the children of this parent process (subject to the restriction of only creating two or three 
processes each). Once again, any process that creates other processes must create either two or three 
processes only, no more and no less.

My Implementation: 
The Initial Process (first gen) will Create 3 Children. The second gen will create 3 childrens each.
Only one child in the third gen will create 2 children

Illustration:
                     0                       	1
            /        |        \	
           0         0         0				3
        /     \    /   \     /   \  
       0       0   0    0    0    0				6
                                /   \
                               0     0 			2     Sum = 12

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
	int current_generation = 1;
	int is__last_child_second_generation = false;
	int is_last_child_third_generation = false;
	while (1){
		switch(current_generation){
			case 1:
			//First Generation ( initial Process)
				for(int i=0; i<3; i++){	
				// Create 3 child processes
					if(i==2)
					//On the last child "mark him with this last_child_boolean" - so he's different
						is__last_child_second_generation=true;
					result = fork();

					// Handle Error
					if (result == -1) {
						printf("Error Creating Child");
					}else if (result != 0) {
					// This is a parent process
						if(i==0)	//So it only prints once
							printf("Initial Process, Generation %d\n",current_generation);
						else if(i==2){
						//After you created all your children, wait for them to die
							waitpid(-1, &status, 0);
						//... Then you die with then... romeo juliet story here...
							exit(0);
						}	
					} else {
					// This is a child process. Increase their Generation
						current_generation++;
						printf("Created child, Generation: %d \n",current_generation);
						break;
					}
				}
				break;
			case 2:
			//Second Generation Children
				for(int i=0; i<2; i++){
				//Each Second Generation will create 2 childen... that was fast...
					result = fork();
					if(is__last_child_second_generation && i==1)
					//Again, mark the last child so you can differtiate him later
						is_last_child_third_generation = true;
					// Handle Error
					if (result == -1) {
						printf("Error Creating Child");
					}else if (result != 0) {
					//child is now a parent!! 
						if(i==1){
							waitpid(-1, &status, 0);
							exit(0);
						}	
					} else {
					// This is a grandchild process
						current_generation++;
						printf("Created child, Generation: %d \n",current_generation);
						break;
					}
				}
				break;
			case 3:
				if(is_last_child_third_generation){
				//only the last child should have children
					for(int i=0; i<2; i++){
						result = fork();
						// Handle Error
						if (result == -1) {
							printf("Error Creating Child");
						}else if (result != 0) {
						// This is a parent process
							if(i==1){
								waitpid(-1, &status, 0);
								exit(0);
							}	
						} else {
						// This is a child process
							current_generation++;
							printf("Created child, Generation: %d \n",current_generation);
							break;
						}
					}
				}
				exit(0);
				break;
			default:
				exit(0);
				break;
		}

	}

	exit(0);

	return 0;
}
