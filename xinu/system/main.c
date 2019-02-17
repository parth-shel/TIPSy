/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void cpubound(void);
extern void iobound(void);

process	main(void)
{
	kprintf("\nHello World!\n");

        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));
        resume(create((void*) cpubound, 1024, 50, "cpubound", 0, NULL));

        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));
        resume(create((void*) iobound, 1024, 50, "iobound", 0, NULL));

        //recvclr();
        //resume(create(shell, INITSTK, 50, "shell", 1, CONSOLE));

        kill(currpid);

	// Wait for shell to exit and recreate it

	while (TRUE) {
		receive();
		// resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
