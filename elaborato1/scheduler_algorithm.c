/// @file scheduler_algorithm.c
/// @brief Round Robin algorithm.
/// @date Mar 2019.

#include "prio.h"
#include "debug.h"
#include "assert.h"
#include "list_head.h"
#include "scheduler.h"

#define GET_WEIGHT(prio) prio_to_weight[USER_PRIO((prio))]
#define NICE_0_LOAD GET_WEIGHT(DEFAULT_PRIO)

task_struct *pick_next_task(runqueue_t *runqueue, time_t delta_exec)
{
	// Pointer to the next task to schedule.
	task_struct *next = NULL;

#if defined(SCHEDULER_RR)
	//==== Implementation of the Round-Robin Scheduling algorithm ============

	// get the next process after the current one
	list_head *nNode = runqueue->curr->run_list.next ;

	// check if we reached the head of list_head
	if (nNode == runqueue -> queue )
		nNode = nNode -> next;

	// get the task_struct
	task_struct *next = list_entry(nNode, task_struct, run_list);

	//=======================================================================
#elif defined(SCHEDULER_PRIORITY)
	//==== Implementatin of the Priority Scheduling algorithm ===============

	// get the first element of the list
	next = list_entry(/*...*/);

	// Get its static priority.
	time_t min = /*...*/

	list_head *it;
	// Inter over the runqueue to find the task with the smallest priority value
	list_for_each (it, &runqueue->queue) {
		task_struct *entry = list_entry(/*...*/);
		// Check entry has a lower priority
		if (/*...*/) {
			/*...*/
		}
	}

	//=======================================================================
#elif defined(SCHEDULER_CFS)
	//==== Implementatin of the Completely Fair Scheduling ==================

	// Get the weight of the current process.
	// (use GET_WEIGHT macro!)
	int weight = /*...*/

	if (weight != NICE_0_LOAD) {
		// get the multiplicative factor for its delta_exec.
		double factor = /*...*/

		// weight the delta_exec with the multiplicative factor.
		delta_exec = // ...
	}

	// Update vruntime of the current process.
	// ...

	// Get the first element of the list
	next = // ...

	// Get its virtual runtime.
	time_t min = // ...

	// Inter over the runqueue to find the task with the smallest vruntime value
	// ...


	//========================================================================
#else
#error "You should enable a scheduling algorithm!"
#endif
	assert(next && "No valid task selected.");

	//dbg_print("Selected %d\n", next->pid);

	return next;
}
