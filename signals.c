#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static volatile int count1 = 0, count2 = 0;
static volatile int isExit = 0;

void mysignal_handler(int signalNo) {
	switch(signalNo) {
		case SIGUSR1:
			//printf("SIGUSR1 [%d] rised\n", SIGUSR1);
			count1++;
			break;
		case SIGUSR2:
			//printf("SIGUSR2 [%d] rised\n", SIGUSR2);
			count2++;
			break;
		case SIGTERM:
			//printf("SIGTERM [%d] rised\n", SIGTERM);
			isExit = 1;
			break;
	}
}

int main() {
	signal(SIGUSR1, mysignal_handler);
	signal(SIGUSR2, mysignal_handler);
	signal(SIGTERM, mysignal_handler);

	while(1) {

/*		usleep(500);
		raise(SIGUSR1);
		usleep(500);
		raise(SIGUSR1);

		usleep(500);
		raise(SIGUSR2);
		usleep(500);
		raise(SIGUSR2);
		usleep(500);
		raise(SIGUSR2);

		usleep(500);
		raise(SIGTERM);*/


		usleep(500);
		if (isExit == 1) {

			printf("%d %d\n", count1, count2);
			fflush(stdout);

			_exit(0);
		}


	}
}



