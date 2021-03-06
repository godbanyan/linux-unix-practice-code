/* hello2.c
 * purpose:	show how to use curses functions with a loop
 * outline:	initialize, draw stuff, wrap up             
*/

#include <stdio.h>
#include <curses.h>

void main(void)
{
	int i;
	initscr();			/*turn on curses*/

	clear();			/*clear screen*/
	for (i = 0; i < LINES; i++){
		move(i, i + 1);
		if (i % 2 == 1)
			standout();
		addstr("Hello, world");
		if (i % 2 == 1)
			standend();
	}
	refresh();
	getch();
	endwin();			/*turn off curses*/
}
