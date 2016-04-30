#include <ksyscall.h>
#include <proc.h>
#include <lib/string.h>

int syscall_page_map(int srcpid, uint32_t srcva, 
	int destpid, uint32_t destva, int perm)
{
	struct Process *srcproc, *destproc;
	if(pid2proc(srcpid, &srcproc) < 0
		|| pid2proc(destpid, &destproc) < 0) {
		return -1;
	}

	if(srcva >= USER_TOP || srcva != ROUND_DOWN(srcva, PAGE_SIZE)
		|| destva >= USER_TOP || destva != ROUND_DOWN(destva, PAGE_SIZE)) {
		return -1;
	} 

	// PageTableEntry *pte;
	// char *page = (char *)page_lookup(srcproc->vm, srcva, &pte);
	uint32_t pa = resolve_physical_address(srcproc->vm, srcva);

	// see if there's some way to check through the pte that the access perms are correct.

	map_pages(destproc->vm, (struct MemoryMapping){
		destva,
		pa,
		pa + PAGE_SIZE,
		AP_RW_RW
	});

	return 0;
}
