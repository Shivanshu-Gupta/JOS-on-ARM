// User-level IPC library routines

#include <lib/syscall.h>
#include <lib/stdio.h>
#include <vm.h>

uint32_t
ipc_recv(int *srcpid, void *pg, uint32_t *perm_store)
{
	void *dstva = (pg == NULL ? (void *)(USER_TOP + 1) : pg);

	// printf("ipc_recv : calling sys_ipc_recv\n");
	int r = sys_ipc_recv((uint32_t)dstva);
	// printf("ipc_recv : r = %d\n", r);
	if(r < 0) {
		if(srcpid != NULL)
			*srcpid = 0;
		return r;
	}
	
	uint32_t value;
	sys_ipc_data(srcpid, &value, perm_store);

	return value;
}

void
ipc_send(int destpid, uint32_t value, void *pg, uint32_t perm)
{
	int r;
	uint32_t srcva = (pg == NULL ? (USER_TOP + 1) : (uint32_t)pg);
	
	while(1) {
		r = sys_ipc_try_send(destpid, value, srcva, perm);
		// printf("r = %d\n", r);
		if(r == 0)
			return;
		else if(r == -2) {
			yield();
		} else {
			printf("ipc_send : %d\n", r);
		}
		
	}
}

// uint32_t
// // ipc_recv(int *srcpid, void *pg, int *perm_store)
// ipc_recv_pg(int *srcpid, void *pg, int *perm_store)
// {
// 	if(pg == NULL) {
// 		return -1;
// 	}

// 	int r = sys_ipc_recv_pg((uint32_t)pg);
// 	if(r < 0) {
// 		if(srcpid != NULL)
// 			*srcpid = 0;
// 		return r;
// 	}
	
// 	sys_ipc_data(srcpid, NULL, perm_store);

// 	return 0;
// }