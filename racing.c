// Deven Bernard 10099810
// Marissa Huang 10179169
// Kevin Zuern 10134425
// Quentin Petraroia 10145835

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_LANES 5
#define MAX_PROGRESS 40
#define MILLISECONDS 1000

// playerPosition is a void * to an int. This function increments the int at random times
// until the int is no longer < MAX_PROGRESS
void* cpu_player(void* playerPosition) {
	while (*(int*)playerPosition < MAX_PROGRESS) {
		// sleeptime is in [0ms, 100ms] but stored in microseconds.
		unsigned int sleepTime = (rand() % 100 ) * MILLISECONDS;
		usleep(sleepTime);
		// Update progress
		++*(int*)playerPosition;
	}

	return 0;
}

// playerPosition is same as cpu_player
void* human_player(void* playerPosition) {
	while ( *(int*)playerPosition < MAX_PROGRESS ) {
		char input = fgetc(stdin);
		if (input == '\n') // if character is a carriage return
			++*(int*)playerPosition;
	}

	return 0;
}

void printHeading() {
	printf("Welcome to CISC220 Racing Arena\n");
	printf("Hit Enter to move forward\n");
}

void drawLane(int playerPosition, int laneNumber) {
	char* car    = "|->";
	char* tail   = "~";
	char* space  = " ";

	// print the ~~~~~~~ trail behind the car
	for (int i = 0; i < playerPosition; ++i)
		printf("%s", tail);
	// print the car
	printf("%s", car);

	// print whitespace to fill remaining space
	for (int i = 0; i < MAX_PROGRESS - playerPosition; ++i)
		printf("%s", space);
	// print lane number
	printf("# LANE %d #\n", laneNumber);
}

void* drawGame(void* playerPositions) {
	int* positions = (int*)playerPositions;

	int gameOver;
	int winner;

	// main drawing loop
	do {
		// Check if the game is ending this frame
		for (int i = 0; i < NUM_LANES; ++i)
			if (positions[i] >= MAX_PROGRESS) {
				gameOver = 1;
				winner = i+1;
				break;
			}
		usleep(20 * MILLISECONDS);
		system("clear");
		printHeading();
		for (int i = 0; i < NUM_LANES; ++i)
			drawLane( positions[i], i+1);
		if (gameOver)
			printf("Player %d WINS\n", winner);
	} while (!gameOver);
	
	return 0;
}

int main(int argc, char const *argv[])
{
	// Create Player thread array (players[0] is the human)
	pthread_t players[NUM_LANES];
	// Create the progress array (progress[0] is the human)
	int progress[NUM_LANES];
	// Initialize the array
	for(int i = 0; i < NUM_LANES; ++i)
		progress[i] = 0;

	do {
		system("clear");
		printHeading();
	}
	while (fgetc(stdin) != '\n');


	// Create & Start the CPU threads
	for (int i = 1; i < NUM_LANES; ++i)
		pthread_create(&players[i], NULL, cpu_player, &progress[i]);

	// Create & Start Human Player Thread
	pthread_create(&players[0], NULL, human_player, &progress[0]);

	// Create Draw Thread
	pthread_t draw;
	pthread_create(&draw, NULL, drawGame, progress );

	// Join main thread to draw thread to force main to wait until game is over
	pthread_join(draw, NULL);

	return 0;
}
