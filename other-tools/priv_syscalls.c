//
//  priv_syscalls.cpp
//  dyld
//
//  Created by Hayes Dombroski on 1/23/25.
//

#include "priv_syscalls.h"

#include <mach/mach_types.h>
#include <errno.h>

int task_read_for_pid(mach_port_name_t target_tport, int pid, mach_port_name_t *t) {
    long result;
    long syscall_number = 0x21B; // System call number for task_read_for_pid

    __asm__ volatile (
        "mov x16, %1\n"        // Move syscall_number into x16
                      "mov x0, %x2\n"         // Move target_tport into x0
                      "mov x1, %x3\n"         // Move pid into x1
        "mov x2, %4\n"         // Move t (pointer) into x2
        "svc #0\n"             // Supervisor Call to invoke the system call
        "mov %0, x0\n"         // Move return value from x0 to result
        : "=r"(result)         // Output operand
        : "r"(syscall_number), "r"(target_tport), "r"(pid), "r"(t)  // Input operands
        : "x0", "x1", "x2", "x16", "memory", "cc"  // Clobbers
    );

    // Check for errors (negative return value)
    if (result < 0) {
        errno = (int)-result;  // Set errno to the positive error code
        return -1;             // Indicate failure
    }

    // On success, result contains the return value (e.g., port name)
    return (int)result;
}

