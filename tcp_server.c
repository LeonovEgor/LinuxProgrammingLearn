#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in local;
#define BUFSIZE 5 * 1024

bool isOff(char buffer[]) {
	return strcmp(buffer, "OFF\n") == 0? true: false;
}

int comp (const void * elem1, const void * elem2)
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if (f < s) return 1;
    if (f > s) return -1;
    return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("В качестве аргумента укажите порт сервера.");
		exit(-1);
	}
	int port = atoi(argv[1]);

	int s = socket(AF_INET, SOCK_STREAM, 0);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(port);
	local.sin_family = AF_INET;

	bind(s, (struct sockaddr*) &local, sizeof(local));
	listen(s, 5);

	int accept_socket = accept(s, NULL, NULL);
	char buffer[BUFSIZE] = {0};

	while(1) {

		size_t n = read(accept_socket, buffer, BUFSIZE);
		if (n == -1) continue;

		if (isOff(buffer)) exit(0);

		//printf("received %s\n", buffer);
		qsort(buffer, strlen(buffer), 1, comp);
		//printf("sorted   %s\n", buffer);

		write(accept_socket, buffer, strlen(buffer)+1);

		memset(buffer, 0, n);
	}
}



