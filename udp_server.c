/*
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
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

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("В качестве аргумента укажите порт сервера.");
		exit(-1);
	}
	int port = atoi(argv[1]);

	int s = socket(AF_INET, SOCK_DGRAM, 0);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(port);
	local.sin_family = AF_INET;

	bind(s, (struct sockaddr*) &local, sizeof(local));


	char buffer[BUFSIZE] = {0};

	while(1) {

		size_t n = read(s, buffer, BUFSIZE);
		if (n == -1) continue;

		if (isOff(buffer)) exit(0);

		printf("%s\n", buffer);

		memset(buffer, 0, n);
	}
}

*/
