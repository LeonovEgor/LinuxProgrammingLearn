#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int hasSubstring(char *str, char *subStr);
int isNumber(char * str);
char* getProcName(char *procId);


       int main(void)
       {
           struct dirent **namelist;
           int dirCount;

           dirCount = scandir("/proc", &namelist, NULL, alphasort);
           if (dirCount == -1) {
               perror("scandir");
               exit(EXIT_FAILURE);
           }

	   int count = 0;
	   int item = dirCount;	

           while (item--) {
		if (isNumber(namelist[item]->d_name) > 0) {
                  //printf("%s\n", namelist[item]->d_name);
		  char *name = getProcName(namelist[item]->d_name);
		  if (hasSubstring(name, "genenv") > 0) {
			count++;
	          }
		}

               free(namelist[item]);
           }
           free(namelist);

	   printf("%d\n", count);

           exit(EXIT_SUCCESS);
       }


int isNumber(char * str) 
{
  int i;
  //printf("strlen: %ld\n", strlen(str));

  for(i = 0; i < strlen(str); i++) {
    if (isdigit(str[i]) == 0) return 0;
  }

  return 1;
}

char* getProcName(char *procId) 
{
  char stat_file[1000] = {0};
  sprintf(stat_file, "/proc/%s/comm", procId);

  FILE *fd = fopen(stat_file, "r");

  char proc_name[256];
  fscanf(fd, "%s", proc_name);
  //printf("%s\n", proc_name);

  fclose(fd);
  
  char *name = (char*) malloc(strlen(proc_name) + 1);
  strcpy(name, proc_name);

  return name;
}

int hasSubstring(char *str, char *subStr) 
{
  if (strstr(str, subStr) != NULL) return 1;
  return 0;
}


