/* setquota.c - setquota */

#include <xinu.h>

syscall setquota (pid32 pid, uint32 ms) {
    intmask mask;
    struct procent *prptr;
    mask = disable();
    if (isbadpid(pid)) {
        restore(mask);
        return SYSERR;
    }
    prptr = &proctab[pid];
    prptr->prquota = ms;
    restore(mask);
    return OK;
}
