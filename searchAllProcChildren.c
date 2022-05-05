#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int getParentPid(int procId);
bool isNumber(char *str);
bool isChieldOfParent(int pid, int searchedParentId);

int main(int n, char *arr[]) {
	if (n < 1) {
		printf("Enter process number in argument!");
		return -1;
	}
	int procId = atoi(arr[1]);

	//printf("arr1: %d\n", procId);

	struct dirent **namelist;
    int dirCount = scandir("/proc", &namelist, NULL, alphasort);
    if (dirCount == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

	int item = dirCount;
	int count = 1;

    while (item--) {
    	//printf("d_name: %s\n", namelist[item]->d_name);
		if (isNumber(namelist[item]->d_name)) {
			int id = atoi(namelist[item]->d_name);
			//printf("id: %d\n", id);
		  if (isChieldOfParent(id, procId)) {
			count++;
		   }
		}

        free(namelist[item]);
    }
    free(namelist);

    //printf("count: %d\n", count);
    printf("%d\n", count);

	return EXIT_SUCCESS;
}

bool isChieldOfParent(int pid, int searchedParentId) {

	//printf("%d", pid);

	while(pid != 1 && pid != 0) {
		pid = getParentPid(pid);

		//printf("<-%d", pid);

		if (pid == searchedParentId) return true;
	}

	//printf(";\n");

	return false;
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

bool isNumber(char *str)
{
  int i;
  for(i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) return false;
  }

  return true;
}
