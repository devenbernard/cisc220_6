#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// Deven Bernard 10099810
// Marissa Huang 10179169
// Kevin Zuern 10134425
// Quentin Petraroia 10145835

void* human(void *args){
	pthread lane1;
	int pthread_create(pthread_t *lane1, NULL, void *(*human)(void *), void *arg);
}

int main() {
	system("clear");
	printf("Welcome to CISC220 Racing Arena\nHit Enter to move forward\n");
	char *playerLane = "|->                                        # Lane 1 #";
	char *laneTwo = "|->                                        # Lane 2 #";
	char *laneThree = "|->                                        # Lane 3 #"; 
	char *laneFour = "|->                                        # Lane 4 #";
	char *laneFive = "|->                                        # Lane 5 #";
	printf("%s\n%s\n%s\n%s\n%s\n", playerLane, laneTwo, laneThree, laneFour, laneFive);
return 0;
}
