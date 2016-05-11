#include <ksyscall.h>
#include <proc.h>
#include <klib.h>
#include <lib/string.h>

// int syscall_ipc_try_send(int pid, uint32_t value, uint32_t srcva, int perm)
int syscall_ipc_try_send(int pid, uint32_t value)
{
	// kprintf("syscall_ipc_try_send : pid = %d, value = %d\n", pid, value);
	struct Process *proc;
	if(pid2proc(pid, &proc) < 0) {
		return -1;
	}
	
	if(!proc->proc_ipc_recving || (proc->proc_ipc_from != 0 && proc->proc_ipc_from != current_process->pid)) {
		// kprintf("proc not ready to recv yet!\n");
		return -2;
	}

	// // if(srcva >= USER_TOP || srcva != ROUND_DOWN(srcva, PAGE_SIZE)) {
	// // 	return -1;
	// // }

	// //perm settings case not handled
	// if(proc->proc_ipc_dstva < USER_TOP && srcva < USER_TOP) {
	// 	//receiver wants to receive
	// 	struct PageTableEntry *pte;
	// 	char *page = (char *)page_lookup(current_process->vm, srcva, &pte);
		
	// 	if((perm & AP_RW_RW) && ((pte->access_permissions & AP_RW_RW) == 0)) {
	// 		return -1;
	// 	}

	// 	map_pages(proc->vm, (struct MemoryMapping){
	// 		proc->proc_ipc_dstva,
	// 		V2P(page),
	// 		V2P(page) + PAGE_SIZE,
	// 		perm
	// 	});
	// }
	
	// proc->proc_ipc_perm = perm;
	proc->proc_ipc_recving = 0;
	proc->proc_ipc_from = current_process->pid;
	proc->proc_ipc_value = value;
	proc->state = READY;

	return 0;
}
