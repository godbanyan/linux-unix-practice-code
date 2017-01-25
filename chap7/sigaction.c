/* sigactdemo.c
 *			purpose: shows use of sigaction()
 *			feature: blocks ctrl-\ while handling ctrl-C
 *					does not reset ctrl-C handler, so two kill
 */

#include <stdio.h>
#include <signal.h>
#define INPUTLEN	100

void main(void)
{
	struct sigaction newhandler;
	sigset_t	blocked;			/*set of blocked sigs*/
	void		inthander();
	char		x[INPUTLEN];

	/* load these two members first */
	newhandler.sa_handler = inthander;
	newhandler.sa_flags = SA_RESETHAND | SA_RESTART;

	/* then build the list of blocked signales */
	sigemptyset(&blocked);			/* clear all bits */
	sigaddset(&blocked, SIGQUIT);	/* add SIGQUIT to list */
	newhandler.sa_mask = blocked;	/* store blockmask */

	//sigprocmask(SIG_BLOCK, &blocked, NULL);

	if (sigaction(SIGINT, &newhandler, NULL) == -1)
		perror("sigaction");
	else
		while(1){
			fgets(x, INPUTLEN, stdin);
			printf("input: %s", x);
		}
}

void inthander(int s)
{
	printf("Called with signal %d\n", s);
	sleep(s);
	printf("done handling signal %d\n", s);
}
