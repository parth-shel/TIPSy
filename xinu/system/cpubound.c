/* cpubound */

#include <xinu.h>

void cpubound() {
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            // calculate i^j
            uint32 base = i, exponent = j;
            long long result = 1;
            while (exponent != 0) {
                result *= base;
                exponent--;
            }

            // calculate j^i
            base = j, exponent = i;
            result = 1;
            while (exponent != 0) {
                result *= base;
                exponent--;
            }

            // calculate hailstone sequence
            uint32 num = 300;
            while(num != 1) {
                if (num%2 == 0) {
                    num /= 2;
                } else {
                    num = num*3+1;
                }
            }

            // perform memcpy
            char src[] = "hello world!";
            char dest[15];
            memcpy(dest, src, strlen(src)+1);
        }
    }

    kprintf("CPU bound process.\n");

    kprintf("PID: %d\n", currpid);
    kprintf("CPU time: %d\n", getcputime(currpid));
    kprintf("priority: %d\n", getprio(currpid));
}
