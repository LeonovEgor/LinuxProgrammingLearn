#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <fcntl.h>


int main() {
	int fds[2];
	char buf[4096];

	int i, rc, maxfd;
	fd_set watchset; /* fds для чтения */
	fd_set inset; /* обновляется select() */

	/* открыть оба канала */
	if ((fds[0] = open("in1", O_RDONLY | O_NONBLOCK)) < 0) {
		perror("open in1");
		return 1;
	}


	if ((fds[1] = open("in2", O_RDONLY | O_NONBLOCK)) < 0) {
		perror("open in2");
		return 1;
	}

	/* начать чтение из обоих файловых дескрипторов */
	FD_ZERO(&watchset);
	FD_SET(fds[0], &watchset);
	FD_SET(fds[1], &watchset);

	/* найти максимальный файловый дескриптор */
	maxfd = fds[0] > fds[1] ? fds[0] : fds[1];

	int sum = 0;
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	/* пока наблюдаем за одним из fds[0] или fds[1] */
	while (FD_ISSET(fds[0], &watchset) ||  FD_ISSET(fds[1], &watchset)) {
		/* здесь копируем watchset, потому что select() обновляет его */
		inset = watchset;
		if (select(maxfd + 1, &inset, NULL, NULL, &tv) < 0) {
			perror("select");
			return 1;
		}

		/* проверить, какой из файловых дескрипторов готов для чтения из него */
		for (i = 0; i < 2; i++) {
			if (FD_ISSET(fds[i], &inset )) {
				/* fds[i] готов для чтения, двигаться дальше... */
				rc = read(fds[i], buf, sizeof (buf) - 1);
				if (rc < 0) {
					perror("read");
					return 1;
				} else if (!rc) {
					/* этот канал закрыт, не пытаться читать из него снова */
					close(fds[i]);
					FD_CLR(fds[i], &watchset);
				} else {
					buf[rc] = 0;
					//printf("чтение: %s\n", buf);
					int number = atoi(buf);
					sum += number;
				}
			}
		}
	}

	printf("%d", sum);

	return 0;
}
