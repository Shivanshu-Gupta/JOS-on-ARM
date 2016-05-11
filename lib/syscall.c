#include <lib/syscall.h>
#include <lib/stdio.h>
#include <types.h>

int syscall0(enum SystemCallCode code)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));
	
	return result;
}

int syscall1(enum SystemCallCode code, int arg1)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("ldr r1, %0" : : "m" (arg1));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));
	
	return result;
}

int syscall2(enum SystemCallCode code, int arg1, int arg2)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("ldr r1, %0" : : "m" (arg1));
	__asm__ volatile("ldr r2, %0" : : "m" (arg2));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));
	
	return result;
}

int syscall3(enum SystemCallCode code, int arg1, int arg2, int arg3)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("ldr r1, %0" : : "m" (arg1));
	__asm__ volatile("ldr r2, %0" : : "m" (arg2));
	__asm__ volatile("ldr r3, %0" : : "m" (arg3));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));

	return result;
}

int syscall4(enum SystemCallCode code, int arg1, int arg2, int arg3, int arg4)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("ldr r1, %0" : : "m" (arg1));
	__asm__ volatile("ldr r2, %0" : : "m" (arg2));
	__asm__ volatile("ldr r3, %0" : : "m" (arg3));
	__asm__ volatile("ldr r4, %0" : : "m" (arg4));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));

	return result;
}

int syscall5(enum SystemCallCode code, int arg1, int arg2, int arg3, int arg4, int arg5)
{
	int result;

	__asm__ volatile("ldr r0, %0" : : "m" (code));
	__asm__ volatile("ldr r1, %0" : : "m" (arg1));
	__asm__ volatile("ldr r2, %0" : : "m" (arg2));
	__asm__ volatile("ldr r3, %0" : : "m" (arg3));
	__asm__ volatile("ldr r4, %0" : : "m" (arg4));
	__asm__ volatile("ldr r5, %0" : : "m" (arg5));
	__asm__ volatile("swi #0");
	__asm__ volatile("str r0, %0" : "=m" (result));

	return result;
}

void putch(int c)
{
	syscall1(SYSCALL_PUTCH, c);
}

int getch(void)
{
	return syscall0(SYSCALL_GETCH);
}

void exit(int code)
{
	syscall1(SYSCALL_EXIT, code);
}

int getpid(void)
{
	return syscall0(SYSCALL_GETPID);
}

int fork(void)
{
	return syscall0(SYSCALL_FORK);
}

void exec(int id)
{
	syscall1(SYSCALL_EXEC, id);
}

void yield(void)
{
	syscall0(SYSCALL_YIELD);
}

void wait(int id)
{
	syscall1(SYSCALL_WAIT, id);
}

int page_alloc(int pid, uint32_t va, int perm)
{
	return syscall3(SYSCALL_PAGE_ALLOC, pid, va, perm);
}

int page_map(int srcpid, uint32_t srcva, int destpid, uint32_t destva, int perm)
{
	return syscall5(SYSCALL_PAGE_MAP, srcpid, srcva, destpid, destva, perm);
}

int page_unmap(int pid, uint32_t va)
{
	return syscall2(SYSCALL_PAGE_UNMAP, pid, va);
}

int sys_ipc_try_send(int pid, uint32_t value, uint32_t srcva, uint32_t perm) 
{
	// printf("sys_ipc_try_send : pid = %d, value = %d, srcva = %x, perm = %d\n", pid, value, srcva, perm);
	uint32_t data[] = {value, srcva, perm};
	return syscall2(SYSCALL_IPC_TRY_SEND, pid, (uint32_t)data);
}

int sys_ipc_recv(uint32_t dstva) 
{
	return syscall1(SYSCALL_IPC_RECV, dstva);
}

void sys_ipc_data(int *srcpid, uint32_t *value_store, uint32_t *perm_store) 
{
	uint32_t *data_stores[] = {value_store, perm_store};
	syscall2(SYSCALL_IPC_DATA, (uintptr_t)srcpid, (uintptr_t)data_stores);
}