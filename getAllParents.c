#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int getParentPid(int procId);

int main(int n, char *arr[]) {
	if (n < 1) {
		printf("Enter process number in argument!");
		return -1;
	}
	int procId = atoi(arr[1]);

	printf("%d\n", procId);

	while(procId != 1) {
		procId = getParentPid(procId);
		printf("%d\n", procId);
	}

	return 0;
}

int getParentPid(int procId) {
	  char stat_file[1000] = {0};
	  sprintf(stat_file, "/proc/%d/stat", procId);

	  FILE *fd = fopen(stat_file, "r");

	  int ppid;
	  fscanf(fd, "%*d %*s %*c %d", &ppid);
	  //printf("%d\n", ppid);

	  fclose(fd);

	  return ppid;
}
