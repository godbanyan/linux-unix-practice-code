/* play_again3.c
 * purpose: ask if user wants another transaction
 * method: set tty into char-by-char mode and no-echo mode
 			set tty into no-delay mode
			read char, return result
 * return: 0=>yes, 1=>no, 2=>timeout
 * better: reset terminal mode on Interrupt
 */

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#define ASK			"Do you want another transaction"
#define TRIES		3
#define SLEEPTIME	2
#define BEEP 		putchar('\a');

int get_response(char * question, int maxtries);
void set_nodelay_mode(void);
void set_cr_noecho_mode(void);

int main()
{
	int response;
	tty_mode(0);
	set_cr_noecho_mode();
	set_nodelay_mode();
	response - get_response(ASK,TRIES);
	tty_mode(1);
	return response;
}

int get_response(char * question, int maxtries)
{
	int input;
	printf("%s(y/n)?\n", question);
	fflush(stdout);
	while (1){
		sleep(SLEEPTIME);
		input = tolower(get_ok_char());
		if (input == 'y')
			return 0;
		if (input == 'n')
			return 1;
		if (maxtries-- == 0)
		{
			printf("try time %d\n", maxtries);
			return 2;
		}
		BEEP;
	}
}

void set_nodelay_mode()
{
	int termflags;
	termflags = fcntl(0, F_GETFL);		/*read curr. settings*/
	termflags |= O_NONBLOCK;
	fcntl(0, F_SETFL, termflags);
}

get_ok_char()
{
	int c;
	while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL);
	return c;
}
void set_cr_noecho_mode()

/* purpose: put file descriptor 0(i.e. stdin) into chr_by_chr mode
	method: use bits in termios
*/
{
	struct	termios	ttystate;
	tcgetattr(0, &ttystate);	/* read curr. setting */
	ttystate.c_lflag	&= ~ICANON; /*no buffering*/
	ttystate.c_lflag	&= ~ECHO;
	ttystate.c_cc[VMIN] = 1;		/*get 1 char at time*/
	tcsetattr(0, TCSANOW, &ttystate);/*install settings*/
}

/* how == 0=>save current mode, how == 1=>restore mode*/
tty_mode(int how)
{
	static struct termios original_mode;
	static int original_flags;
	if (how == 0){
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
	}
	else{
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}
