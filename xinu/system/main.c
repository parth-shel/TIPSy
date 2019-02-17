/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void cpubound(void);
extern void iobound(void);

extern uint32 ctxswcnt;

sid32 done;

process	main(void) {
	kprintf("\nHello World!\n");

        done = semcreate(10);

        uint32 start_time = clktime;

        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));

        //recvclr();
        //resume(create(shell, INITSTK, 50, "shell", 1, CONSOLE));

        wait(done);

        uint32 end_time = clktime;

        kprintf("Total Simulation time: %d\n", end_time - start_time);
        kprintf("Context Switches: %d\n", ctxswcnt);

        kill(currpid);

	// Wait for shell to exit and recreate it

	while (TRUE) {
		receive();
		// resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
