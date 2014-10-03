//Amandeep Sandhu, student id: 301073950, Oct 2, 2014
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

//maximum length for command
#define LINE_LENGTH 100

int main() {

	//Line to record input, Character to help break apart input, Array to hold tokenized string.
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

		printf("%d:%d:%d#", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		fgets(line, LINE_LENGTH, stdin);
		//record amount of tokens in array
		counter = 0;
		//remove spaces and \n from tokens
		character = strtok(line, " \n");
		//Break string into tokens
		while(character != NULL) {
			array[counter++] = character;
			character = strtok(NULL, " \n");
		}
		//exit command for shell
		if((strcmp("exit", array[0]) == 0) || strcmp("exit()", array[0]) == 0){
			printf("Exiting aman-shell\n");
			return EXIT_SUCCESS;
		}else {
			pcopy = fork();
			//fork succeeded
			if(pcopy >= 0) {
				//Child or copy loop, to execute program
				if(pcopy == 0) {
					exitid = execvp(array[0], array);
					if(exitid < 0) {
						printf("Failed to find command\n");
					}
					return exitid;
				}else {
					//parent waits for child to execute or fail
					waitpid(pcopy, &status, WUNTRACED);
				}
			//Fork failed	
			}else { 
				printf("Failed to create fork");
			}
		}
	}
}