#include <ksyscall.h>
#include <proc.h>
#include <lib/string.h>

int syscall_page_alloc(int pid, uint32_t va, int perm)
{
	struct Process *proc;
	if(pid2proc(pid, &proc) < 0) {
		return -1;
	}

	if(va >= USER_TOP || va != ROUND_DOWN(va, PAGE_SIZE)) {
		return -1;
	} 
	char *page = kalloc();
	memset(page, 0, PAGE_SIZE);

	map_pages(proc->vm, (struct MemoryMapping){
		va,
		V2P(page),
		V2P(page) + PAGE_SIZE,
		AP_RW_RW
	});

	return 0;
}
