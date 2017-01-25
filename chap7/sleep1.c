/* sleep1.c
 * purpose: show how sleep works
 * usage: sleep1
 * outline: sets handler, set alarm, pauses, then returns
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
//#define SHHHH

void main(void)
{
	void wakeup(int);
	printf("about to sleep for 4 seconds\n");
	signal(SIGALRM, wakeup);
	alarm(4);
	pause();
	printf("Monrning so soon?\n");
}

void wakeup(int signum)
{
#ifndef SHHHH
	printf("Alarm received from kernel\n");
#endif
}
