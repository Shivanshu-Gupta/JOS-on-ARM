#include <console.h>
#include <lib/syscall.h>
#include <lib/stdio.h>
#include <klib.h>
#include <proc.h>

static int (*const syscall_handler[])() = {
	[SYSCALL_EXIT] = syscall_exit,
	[SYSCALL_PUTCH] = syscall_putch,
	[SYSCALL_GETCH] = syscall_getch,
	[SYSCALL_GETPID] = syscall_getpid,
	[SYSCALL_FORK] = syscall_fork,
	[SYSCALL_EXEC] = syscall_exec,
	[SYSCALL_YIELD] = syscall_yield,
	[SYSCALL_WAIT] = syscall_wait,
	[SYSCALL_PAGE_ALLOC] = syscall_page_alloc,
	[SYSCALL_PAGE_MAP] = syscall_page_map,
	[SYSCALL_PAGE_UNMAP] = syscall_page_unmap
	[SYSCALL_IPC_TRY_SEND] = syscall_ipc_try_send,
	[SYSCALL_IPC_RECV] = syscall_ipc_recv
};

/* kernel side of system calls. */
int handle_syscall(enum SystemCallCode code, int arg1, int arg2, int arg3, int arg4, int arg5)
{
	return syscall_handler[code](arg1, arg2, arg3, arg4, arg5);
}

int handle_data_abort() {
	kprintf("HEREEEEE\n");
	return 0;
}
