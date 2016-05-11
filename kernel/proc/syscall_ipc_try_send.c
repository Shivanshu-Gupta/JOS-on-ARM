#include <ksyscall.h>
#include <proc.h>
#include <klib.h>
#include <lib/string.h>

int syscall_ipc_try_send(int pid, uint32_t *data)
{
	uint32_t value = data[0], srcva = data[1], perm = data[2];
	struct Process *proc;
	if(pid2proc(pid, &proc) < 0) {
		return -1;
	}
	
	if(!proc->proc_ipc_recving || (proc->proc_ipc_from != 0 && proc->proc_ipc_from != current_process->pid)) {
		return -2;
	}

	if(srcva < USER_TOP && srcva != ROUND_DOWN(srcva, PAGE_SIZE)) {
		return -1;
	}

	//perm settings case not handled
	if(proc->proc_ipc_dstva < USER_TOP && srcva < USER_TOP) {
		kprintf("mapping page in sender:%x to in recver:%x\n", srcva, proc->proc_ipc_dstva);
		//receiver wants to receive
		struct PageTableEntry *pte;
		uint32_t pa = page_lookup(current_process->vm, srcva, &pte);
		
		// if((perm & AP_RW_RW) && ((pte->access_permissions & AP_RW_RW) == 0)) {
		// 	return -1;
		// }

		map_pages(proc->vm, (struct MemoryMapping){
			proc->proc_ipc_dstva,
			pa,
			pa + PAGE_SIZE,
			AP_RW_RW
		});
		
		kprintf("pages mapped\n");
	}
	
	proc->proc_ipc_perm = perm;
	proc->proc_ipc_recving = 0;
	proc->proc_ipc_from = current_process->pid;
	proc->proc_ipc_value = value;
	proc->state = READY;

	return 0;
}
