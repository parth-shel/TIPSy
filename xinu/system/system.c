/* system.c - system */

#include <xinu.h>

syscall system(pid32 pid) {
    intmask mask = disable();
    if (isbadpid(pid)) {
        restore(mask);
        return SYSERR;
    }
    proctab[pid].prbaseprio = 0;
    restore(mask);
    return pid;
}
