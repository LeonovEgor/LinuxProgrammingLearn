#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

	pid_t pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0) {
			printf("%d\n", pid);
			exit(EXIT_SUCCESS);
	}

	umask(0);

	/* Create a new SID for the child process */
    pid_t sid = setsid();
    if (sid < 0) {
            /* Log any failure */
            exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
            /* Log any failure here */
            exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    while (1) {
       /* Do some task here ... */
       sleep(30); /* wait 30 seconds */
    }
}
