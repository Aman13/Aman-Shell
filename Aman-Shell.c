#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


#define LINE_LENGTH 100

int main() {

	//Line to record input, Character to help break apart input, Array to hold the individual characters.
	char line[LINE_LENGTH], *character, *array[LINE_LENGTH];
	//Counter to record the length of the array, i is used in the for loop
	int counter, i, status, exitid;
	//Help keep track of child process
	pid_t pcopy;

	while(1) {
		//Reset array to all NULL
		for(i = 0; i < LINE_LENGTH; i++) {
			array[i] = NULL;
		}
		//Display the time
		time_t now;
		struct tm *currentTime;
		now = time(NULL);
		currentTime = localtime(&now);

		printf("aman-shell:%d:%d:%d#", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		fgets(line, LINE_LENGTH, stdin);
		counter = 0; //Record size of array
		character = strtok(line, " \n");

		//Break string into tokens
		while(character != NULL) {
			array[counter++] = character;
			character = strtok(NULL, " \n");
		}

		if((strcmp("exit", array[0]) == 0) || strcmp("exit()", array[0]) == 0){
			printf("Exiting aman-shell\n");
			return EXIT_SUCCESS;
//		}else if(strcmp("echo", array[0]) == 0) {
//			for(i = 1; i < counter; i++) {
//				printf("%s ",array[i]);
//			}
//			printf("\n");
		}else {
			pcopy = fork();
			//fork succeeded
			if(pcopy >= 0) {
				if(pcopy == 0) {
			//		printf("copy pid:%d\nparent pid:%d\nvalue of copy:%d\n", getpid(), getppid(), pcopy);
					exitid = execvp(array[0], array);
					return exitid;
				}else {
					waitpid(pcopy, &status, WUNTRACED);
					printf("copy process has terminated\n");
				}

			}else { //Fork failed
				printf("Failed to create fork");
			}
		}
	}
}