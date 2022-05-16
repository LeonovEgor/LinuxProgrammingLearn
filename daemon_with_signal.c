#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

static volatile int isExit = 0;

void mysignal_handler(int signalNo) {
	if (signalNo == SIGURG) {
		//printf("Received SIGURG");
		fflush(stdout);
		isExit = 1;
	}
}

void create_deamon(void) {
	pid_t pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	// If we got a good PID, then we can exit the parent process.
	if (pid > 0) {
			printf("%d\n", pid);
			exit(EXIT_SUCCESS);
	}

	umask(0);

	// Create a new SID for the child process
    pid_t sid = setsid();
    if (sid < 0) {
            // Log any failure
            exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if ((chdir("/")) < 0) {
            // Log any failure here
            exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}

int main() {

	signal(SIGURG, mysignal_handler);

	create_deamon();

    while (1) {
       // Do some task here ...
    	//printf("daemon is working\n");
    	usleep(500); // wait 30 seconds
    	if (isExit == 1) {
    		fflush(stdout);
    		_exit(0);
    	}
    }
}


