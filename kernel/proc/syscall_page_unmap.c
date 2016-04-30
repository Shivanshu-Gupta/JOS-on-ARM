#include <ksyscall.h>
#include <proc.h>
#include <lib/string.h>

int syscall_page_unmap(int pid, uint32_t va)
{
	struct Process *proc;
	if(pid2proc(pid, &proc) < 0) {
		return -1;
	}

	if(va >= USER_TOP || va != ROUND_DOWN(va, PAGE_SIZE)) {
		return -1;
	}

	unmap_page(proc->vm, va);
	return 0;
}
