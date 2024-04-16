#include "syscall.h"

.global gethid
gethid:
	li a7, SYS_gethid  # put id to a7
	ecall
	ret
