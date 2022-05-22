/*
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("В качестве аргумента введите имя хоста");
		exit(-1);
	}

	struct hostent *h = gethostbyname(argv[1]);

	if (h == NULL) {
		printf("Не удалось получить данные");
		exit(-2);
	}

	int i = 0;
	while (h->h_addr_list[i] != NULL) {
		struct in_addr *addr = (struct in_addr*)h->h_addr_list[i];
		printf("%s\n", inet_ntoa(*addr));
		i++;
	}
}


*/
