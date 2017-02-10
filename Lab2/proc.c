/*
* Edit Scheduler for Minix Operating System
* File can be found in Proc.c Located in /usr/src/kernel
* NOTE: this file only contains part of the proc.c for minix
*/

/*===========================================================================*
*				pick_proc				     *
*===========================================================================*/
PRIVATE struct proc * pick_proc(void)
{
	/* Decide who to run now.  A new process is selected an returned.
	* When a billable process is selected, record it in 'bill_ptr', so that the
	* clock task can tell who to bill for system time.
	*/
	register struct proc *rp;		/* process to run */
	int q;							/* iterate over queues */

	int flag = 0;				/* Used to check if random priority swap happened */
	int previous = 0;			/* Used to go back to before random pick*/
	/* Check each of the scheduling queues for ready processes. The number of
	* queues is defined in proc.h, and priorities are set in the task table.
	* The lowest queue contains IDLE, which is always ready.
	*/
	for (q=0; q < NR_SCHED_QUEUES; q++) {
		if (randFlag == 1){		// allows the queue to end so it can exit loop
			q = previous+1;		// increases q so it will eventually leave 7-15
			flag = 0;			// setting flag so random wasn't set
		}
		// Can't mess with 0-6 because thats the important kernel stuff
		// it'll mess it up the kernel
		if(q > 6){
			previous = q;		// Saves the current queue state so it can go back
			q = rand()%9 + 7; 	// We can change priorities from queues 7 - 15
			flag = 1;			//triggers flag - random happened
		}
		if(!(rp = rdy_head[q])) {
			TRACE(VF_PICKPROC, printf("queue %d empty\n", q););
			continue;
		}

		#if DEBUG_RACE
		rp = random_process(rdy_head[q]);
		#endif

		TRACE(VF_PICKPROC, printf("found %s / %d on queue %d\n",
		rp->p_name, rp->p_endpoint, q););
		assert(proc_is_runnable(rp));
		if (priv(rp)->s_flags & BILLABLE)
		bill_ptr = rp;		/* bill for system time */
		return rp;
	}
	return NULL;
}
