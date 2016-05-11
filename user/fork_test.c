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
	int who;
	if(fork_result) {
		who = fork_result;
		printf("%d sending %d to %d\n", pid, value, who);
		ipc_send(who, value);
		printf("done sending.\n");
	} else {
		printf("in proc pid %d\n", pid);
		int i = ipc_recv(&who, 0);
		printf("%d recved %d from parent %d!!!!!!!!!!!!!!!!!!!!!\n", pid, i, who);
	}
	exit(0);
}
