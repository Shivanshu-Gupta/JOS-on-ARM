#include <ksyscall.h>
#include <proc.h>
#include <lib/string.h>

int syscall_ipc_data(int *srcpid, uint32_t *value)
{

	if(srcpid != NULL)
		*srcpid = current_process->proc_ipc_from;
	// if(perm_store != NULL)
	// 	*perm_store = current_process->proc_ipc_perm;
	
	if(value != NULL)
		*value = current_process->proc_ipc_value;

	return 0;
}
