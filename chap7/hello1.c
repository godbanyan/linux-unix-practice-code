/* hello1.c
 * purpose:	show the minial calls needed to use curses
 * outline:	initialize, draw stuff, wait for input, quit
*/

#include <stdio.h>
#include <curses.h>

void main(void)
{
	initscr();			/*turn on curses*/

	clear();			/*clear screen*/
	move(10, 20);
	addstr("hello, world");
	move(LINES - 1, 0);
	refresh();
	getch();
	endwin();			/*turn off curses*/
}
