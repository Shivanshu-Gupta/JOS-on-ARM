/*
 * lib/syscall.h
 *
 * Type and function declarations for system calls.
 *
 * (c) 2014 Hadi Moshayedi <hadi@moshayedi.net>
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#include <types.h>

enum SystemCallCode {
	SYSCALL_PUTCH,
	SYSCALL_GETCH,
	SYSCALL_EXIT,
	SYSCALL_GETPID,
	SYSCALL_FORK,
	SYSCALL_EXEC,
	SYSCALL_YIELD,
	SYSCALL_WAIT,
	SYSCALL_PAGE_ALLOC,
	SYSCALL_PAGE_MAP,
	SYSCALL_PAGE_UNMAP,
	SYSCALL_IPC_TRY_SEND,
	SYSCALL_IPC_RECV,
	SYSCALL_IPC_DATA,
	SYSCALL_EXOFORK
};

int syscall0(enum SystemCallCode code);
int syscall1(enum SystemCallCode code, int arg1);
int syscall2(enum SystemCallCode code, int arg1, int arg2);

// lib/syscall.c
void putch(int c);
int getch(void);
void exit(int code);
int getpid(void);
int fork(void);
void exec(int id);
void yield(void);
void wait(int id);
int page_alloc(int pid, uint32_t va, int perm);
int page_map(int srcpid, uint32_t srcva, int destpid, uint32_t destva, int perm);
int page_unmap(int pid, uint32_t va);
// int sys_ipc_try_send(int pid, uint32_t value, uint32_t srcva, int perm);
// int sys_ipc_recv(uint32_t dstva); 
// void sys_ipc_data(int *srcpid, uint32_t *value, int *perm_store);
int sys_ipc_try_send(int pid, uint32_t value);
int sys_ipc_recv(uint32_t dstva); 
void sys_ipc_data(int *srcpid, uint32_t *value);

// lib/ipc.c
// void ipc_send(int destpid, uint32_t val, void *pg, int perm);
// uint32_t ipc_recv(int *srcpid, void *pg, int *perm_store);
void ipc_send(int destpid, uint32_t val);
uint32_t ipc_recv(int *srcpid, void *pg);

#endif
