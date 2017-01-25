/* set_ticker.c
* set_ticker(number_of_millseconds)
* arranges for interval timer to issue SIGALRMs at regular intervals
* return s -1 on error, 0 for ok
* arg in milliseconds, converted into whole seconds and microseconds
* note: set_ticker(0) turns off ticker
*/
#include <sys/time.h>
#include <stddef.h>

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;
	
	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000UL;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
   
