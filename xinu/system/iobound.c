/* iobound */

#include <xinu.h>

extern sid32 done;

void iobound() {
    for (int i = 0; i < 150; i++) {
        sleepms(25);
    }

    intmask mask = disable();

    kprintf("I/O bound process.\n");

    kprintf("PID: %d\n", currpid);
    kprintf("CPU time: %d\n", getcputime(currpid));
    kprintf("priority: %d\n", getprio(currpid));

    restore(mask);

    signal(done);

    kill(currpid);
}
