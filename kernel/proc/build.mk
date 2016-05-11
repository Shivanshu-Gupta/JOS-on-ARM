PROC_DIR = kernel/proc

OBJS += $(PROC_DIR)/proc.o
OBJS += $(PROC_DIR)/save_context.o
OBJS += $(PROC_DIR)/scheduler.o
OBJS += $(PROC_DIR)/syscall_exit.o
OBJS += $(PROC_DIR)/syscall_getpid.o
OBJS += $(PROC_DIR)/syscall_fork.o
OBJS += $(PROC_DIR)/syscall_exec.o
OBJS += $(PROC_DIR)/syscall_yield.o
OBJS += $(PROC_DIR)/syscall_wait.o
OBJS += $(PROC_DIR)/syscall_page_alloc.o
OBJS += $(PROC_DIR)/syscall_page_map.o
OBJS += $(PROC_DIR)/syscall_page_unmap.o
OBJS += $(PROC_DIR)/syscall_ipc_try_send.o
OBJS += $(PROC_DIR)/syscall_ipc_recv.o
OBJS += $(PROC_DIR)/syscall_ipc_data.o
OBJS += $(PROC_DIR)/syscall_exofork.o

