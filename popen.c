#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	//1. sprintf()-  "склеиваем" argv[1] и argv[2] через пробел.
	char file_path[256];
	sprintf(file_path, "%s %s", argv[1], argv[2]);

	//printf("path: %s\n", file_path);

	// 2. popen() то, что получилось, не забываем "r"...
	FILE *fd = popen(file_path, "r");

	char ch = 0;
	int count = 0;
	while(!feof(fd)) {
		ch = fgetc(fd);
		if (ch == '0') {
			//printf("found 0\n");
			count++;
		}
	}

	pclose(fd);

	//printf("count: %d\n", count);
	printf("%d\n", count);

	return 0;
}

