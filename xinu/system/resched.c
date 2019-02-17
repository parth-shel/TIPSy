/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

static uint32 ctxswcnt = 0;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

        if ((currpid != NULLPROC) && (ptold->prstate != PR_FREE)) {
            if (ptold->prquota < UINT_MAX) {
                if (ptold->prtime >= ptold->prquota) {
                    kill(currpid);
                }
            }
            ptold->prprio = ptold->prbaseprio + 2 * ptold->prextprio + ptold->prrecent;
            if (ptold->prprio < MINPRIO) ptold->prprio = MINPRIO;
            else if (ptold->prprio > MAXPRIO) ptold->prprio = MAXPRIO;
        }

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > lastkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = getlast(readylist);
        queuetab[currpid].qnext = EMPTY;
        queuetab[currpid].qprev = EMPTY;
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = 0;		/* Reset time slice for process	*/
        ctxswcnt++;
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
