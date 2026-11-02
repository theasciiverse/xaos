#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include "config.h"
#ifdef CURSES_MOUSEDRIVER
#ifdef USE_NCURSES
#ifdef RENAMED_NCURSES
#include <curses.h>
#else
#include <ncurses.h>
#endif
#else
#include <curses.h>
#endif
#include "aalib.h"
#include "aaint.h"
extern int __curses_is_up;
extern int __curses_keyboard;
extern int __curses_x, __curses_y, __curses_buttons;
#include <term.h>
static int xterm_mouse(void)
{
    char *kmous = tigetstr("kmous");
    return kmous != NULL && kmous != (char *) -1 && kmous[0] == '\033' && kmous[1] == '[';
}
static int curses_init(struct aa_context *context, int mode)
{
    if (!__curses_is_up || !__curses_keyboard)
	return 0;
    if (!mousemask( /*ALL_MOUSE_EVENTS */ BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON2_PRESSED | BUTTON2_RELEASED | BUTTON3_PRESSED | BUTTON3_RELEASED | REPORT_MOUSE_POSITION, NULL))
	return 0;
    /* ncurses asks xterm-style terminals for presses and releases only
       (mode 1000); ask for motion while a button is held too (1002), so
       a drag reaches REPORT_MOUSE_POSITION and the pointer follows it */
    if (xterm_mouse())
	putp("\033[?1002h"), fflush(stdout);
    return 1;
}
static void curses_uninit(aa_context * c)
{
    if (xterm_mouse())
	putp("\033[?1002l"), fflush(stdout);
    mousemask(0, NULL);
}

static void curses_mouse(aa_context * c, int *x, int *y, int *b)
{

#if 0
    static MEVENT m;
    /*while(getmouse(&m)!=OK); */
    while (m.bstate)
	getmouse(&m);
    *x = m.x;
    *y = m.y;
#if 0
    *b = 0;
    if (m.bstate & 4)
	*b |= AA_BUTTON1;
    if (m.bstate & 128)
	*b |= AA_BUTTON2;
    if (m.bstate & 8192)
	*b |= AA_BUTTON3;
#endif
    *b = m.bstate;
#endif
    *x = __curses_x;
    *y = __curses_y;
    *b = __curses_buttons;
}

__AA_CONST struct aa_mousedriver mouse_curses_d =
{
    "curses", "Curses mouse driver 1.0",
    0,
    curses_init,
    curses_uninit,
    curses_mouse,
    NULL,
};
#endif
