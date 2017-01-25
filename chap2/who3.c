/*who1.c - a first version of the two program
  open, read UTMP file, and show results
*/
#include <stdio.h>
#include <utmp.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>


#define SHOWHOST

/*show info()
  display contents of the utmp struct in human readable form
  *note* these sizes should not be hardwired
*/

void show_info(struct utmp *utbufp)
{
	if (utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	printf("%10d", utbufp->ut_time);
	printf(" ");
#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

int main()
{
	struct utmp *utbufp, *utmp_next();

	if (utmp_open(UTMP_FILE) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
		show_info(utbufp);
	utmp_close();
	return 0;
}
