#include <ksyscall.h>
#include <proc.h>
#include <klib.h>
#include <lib/string.h>

int syscall_ipc_recv(uint32_t dstva)
{
	if(dstva < USER_TOP && dstva != ROUND_DOWN(dstva, PAGE_SIZE)) {
		return -1;
	} 

	current_process->proc_ipc_recving = 1;
	current_process->proc_ipc_dstva = dstva;
	current_process->proc_ipc_value = 0;
	current_process->proc_ipc_perm = 0;	

	current_process->state = SLEEPING;
	schedule();
	return 0;
}
