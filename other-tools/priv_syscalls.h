//
//  priv_syscalls.h
//  dyld
//
//  Created by Hayes Dombroski on 1/23/25.
//

#ifndef priv_syscalls_h
#define priv_syscalls_h

#include <mach/mach.h>
#include <errno.h>

int task_read_for_pid(mach_port_name_t target_tport, int pid, mach_port_name_t *t);

#endif /* priv_syscalls_h */
