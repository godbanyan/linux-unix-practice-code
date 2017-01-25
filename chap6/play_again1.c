/* play_again1.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode, read char, return result
 * return: 0=>yes, 1=>no
 * better: do no echo inappropriate input
 */

#include <stdio.h>
#include <termios.h>

#define QUESTION	"Do you want another transaction"

int get_response(char * question);

int main()
{
	int response;
	tty_mode(0);
	set_crmode();
	response - get_response(QUESTION);
	tty_mode(1);
	return response;
}

int get_response(char * question)
{
	int input;
	printf("%s(y/n)?", question);
	while (1){
		switch(input = getchar()){
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
			default:
					printf("\ncannot understand %c,", input);
					printf("Please type y or no \n");
		}
	}
}

/* purpose: put file descriptor 0(i.e. stdin) into chr_by_chr mode
	method: use bits in termios
*/
set_crmode(void)
{
	struct	termios	ttystate;
	tcgetattr(0, &ttystate);	/* read curr. setting */
	ttystate.c_lflag	&= ~ICANON; /*no buffering*/
	ttystate.c_cc[VMIN] = 1;		/*get 1 char at time*/
	tcsetattr(0, TCSANOW, &ttystate);/*install settings*/
}

/* how == 0=>save current mode, how == 1=>restore mode*/
tty_mode(int how)
{
	static struct termios original_mode;
	if (how == 0)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}
