#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_LENGTH 100

int main()
{
	//Line to record input, Character to help break apart input, Array to hold the individual characters.
	char line[LINE_LENGTH], *character, *array[LINE_LENGTH];;
	//Counter to record the length of the array, i is used in the for loop
	int counter, i;

	//Display the time
	time_t now;
	struct tm *currentTime;
	now = time(NULL);
	currentTime = localtime(&now);

	while(1) {
		printf("aman-shell %d:%d:%d# ", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
		fgets(line, LINE_LENGTH, stdin);

		counter = 0; //Record size of array
		character = strtok(line, " ");

		//Break string into tokens
		while(character != NULL) {
			array[counter++] = character;
			character = strtok(NULL, " ");
		}
		//Print whats in array
		for(i = 0; i < counter; i++) {
			printf("%s", array[i]);
		}

	}
	return EXIT_SUCCESS;
}