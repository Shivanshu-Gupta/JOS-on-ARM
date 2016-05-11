#include <ksyscall.h>
#include <proc.h>
#include <lib/string.h>

int syscall_ipc_data(int *srcpid, uint32_t *data_stores[])
{
	uint32_t *value_store = data_stores[0];
	uint32_t *perm_store = data_stores[1];
	
	if(srcpid != NULL)
		*srcpid = current_process->proc_ipc_from;
	
	if(perm_store != NULL)
		*perm_store = current_process->proc_ipc_perm;
	
	if(value_store != NULL)
		*value_store = current_process->proc_ipc_value;

	return 0;
}
