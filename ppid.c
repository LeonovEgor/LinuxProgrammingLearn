#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  pid_t pid = getpid();

  char stat_file[1000] = {0};
  sprintf(stat_file, "/proc/%d/stat", pid);

  FILE *fd = fopen(stat_file, "r");

  int ppid;
  fscanf(fd, "%*d %*s %*c %d", &ppid);
  printf("%d\n", ppid);

  fclose(fd);
  return 0;
}
