#include <lib/stdio.h>
#include <lib/syscall.h>

void _start()
{
	int pid = 0;
	int fork_result = 0;

	fork_result = fork();
	pid = getpid();
	printf("hello from pid: %d, fork returned: %d\n", pid, fork_result);
	int value = 100;
	void *pg = 0x80000000 - 4 * 4096;
	int who;
	if(fork_result) {
		page_alloc(0, (uint32_t)pg, 0xff);
		int *msg = (int *)pg;
		msg[0] = 100;
		msg[1] = 200;
		msg[2] = 300;
		who = fork_result;
		printf("%d sending %d to %d\n", pid, value, who);
		printf("send msg: %d %d %d\n", msg[0], msg[1], msg[2]);
		ipc_send(who, value, pg, 0);
	} else {
		int i = ipc_recv(&who, pg, 0);
		int *msg = (int *)pg;
		printf("%d recved %d from %d\n", pid, i, who);
		printf("recv msg: %d %d %d\n", msg[0], msg[1], msg[2]);
	}
	exit(0);
}
