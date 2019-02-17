/* iobound */

#include <xinu.h>

void iobound() {
    for (int i = 0; i < 150; i++) {
        for (int j = 0; j < 150; j++) {
            kprintf("                                                           \r");
            sleepms(1);
        }
    }

    kprintf("I/O bound process.\n");

    kprintf("PID: %d\n", currpid);
    kprintf("CPU time: %d\n", getcputime(currpid));
    kprintf("priority: %d\n", getprio(currpid));
    kprintf("preempt: %d\n", preempt);
}
