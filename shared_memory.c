/*
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void* attach_shared_memory(key_t key, int isCreate) {

	int flag = isCreate == 1 ? IPC_CREAT | 0666 : 0600;

	int shm_id;
	if((shm_id = shmget(key, 1000, flag)) < 0){
	                printf("Can\'t find shared memory\n");
	                exit(-1);
	            }
	void* shm;
    if ((shm = shmat(shm_id, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    return shm;
}

void detach_shared_memory(const void* addr) {
    if(shmdt(addr) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
}

int main(int argc, char* argv[])
{
	key_t key1 = atoi(argv[1]);
	key_t key2 = atoi(argv[2]);
	key_t key3 = 54321;

	int* sh1 = attach_shared_memory(key1, 0);
	int* sh2 = attach_shared_memory(key2, 0);
	int* sh3 = attach_shared_memory(key3, 1);

	int i;
	for(i = 0; i < 100; i++) {
		sh3[i] = sh1[i] + sh2[i];
		//printf("%d\n", sh3[i]);
	}

	detach_shared_memory(sh1);
	detach_shared_memory(sh2);
	detach_shared_memory(sh3);

	printf("%d\n", key3);

	exit(0);
}
*/
