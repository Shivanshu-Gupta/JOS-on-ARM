// Ping-pong a counter between two processes.
// Only need to start one of these -- splits into two with fork.
#include <lib/stdio.h>
#include <lib/syscall.h>

void
_start()
{
	int who;

	if ((who = fork()) != 0) {
		// get the ball rolling
		printf("send 0 from %d to %d\n", getpid(), who);
		ipc_send(who, 0, 0, 0);
	}

	while (1) {
		uint32_t i = ipc_recv(&who, 0, 0);
		printf("%d got %d from %d\n", getpid(), i, who);
		if (i == 10)
			exit(0);
		i++;
		ipc_send(who, i, 0, 0);
		if (i == 10)
			exit(0);
	}

}

