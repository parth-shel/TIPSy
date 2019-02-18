/* getcputime.c - getcputime */

#include <xinu.h>

/* getcputime - Return the total CPU time used by a process */
syscall getcputime(pid32 pid) {
    intmask mask;
    uint32 cputime;

    mask = disable();
    if (isbadpid(pid)) {
        restore(mask);
        return SYSERR;
    }
    cputime = proctab[pid].prtime;
    if (pid == currpid) {
        uint32 boost = (uint32)(((double) proctab[currpid].prprio / MAXPRIO) * QUANTUM);
        uint32 delta = (QUANTUM + boost) - preempt;
        cputime += delta;
    }
    restore(mask);
    return cputime;
}
