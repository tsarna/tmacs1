/*
 * The functions in this file negotiate with the operating system for
 * characters, and write characters in a barely buffered fashion on the display.
 */
#include        <stdio.h>
#include	"estruct.h"
#include        "edef.h"

#if FSE

#include <exec/types.h>
#include <exec/memory.h>
#include <proto/exec.h>

void freeallmalloced();
void ttflush();
int iCharRaw();
void *Limited_malloc(ULONG bytes);
void Limited_free(void *ptr);
void Limited_MemCleanup();

int CXBRK(void) {return 0;}

#include "bbxbase.h"
#include "bbxshell.h"
#include "bbxdefines.h"

extern struct CallBack *CB;

#define TTIOMAXBUF      256L
static char     scrn_tmp[TTIOMAXBUF+2];
static long     scrn_tmp_p = 0;

int sysop = 0;

void *mypool = NULL;
ULONG bytesmalloced = 0;
ULONG malloclimit = 65536;

ttopen()
{
        term.t_mrow = term.t_nrow =
        	(CB->UL->PageHeight)?(CB->UL->PageHeight - 1):24;

        term.t_mcol = term.t_ncol =
        	(CB->UL->PageWidth)?(CB->UL->PageWidth - 1):80;

	/* on all screens we are not sure of the initial position
	   of the cursor					*/
	ttrow = 999;
	ttcol = 999;

	sysop = (int)(CB->UL->sysop);
}



ttclose()
{
        ttflush();
	Done();
}



ttputc(c)
char c;
{
        scrn_tmp[scrn_tmp_p++] = c;
        if(scrn_tmp_p>=TTIOMAXBUF)
                ttflush();
}


void
ttflush()
{
        if(scrn_tmp_p) {
        	scrn_tmp[scrn_tmp_p] = '\0';
        	oLineRaw(scrn_tmp);
	}
        scrn_tmp_p = 0;
}



ttgetc()
{
        char ch;

	if (UserGone())
		exit(0);

        ttflush();
	ch = iCharRaw();

        return(255 & (int)ch);
}

#if	TYPEAH
/* typahead:	Check to see if any characters are already in the
		keyboard buffer
*/

typahead()
{
	if (iReady() != 0)
		return(TRUE);
	else
		return(FALSE);
}
#endif


#ifndef HAVEICHARRAW
int
iCharRaw()
{
	while (!iReady()) {
		if (UserGone())
			exit(0);

		Delay(2);
	}

	if (UserGone())
		exit(0);

	return GetCharRaw();
}
#endif


#if 1

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

void *
Limited_malloc(ULONG bytes)
{
	static ULONG *mem;

	mem  = NULL;

	if ((bytesmalloced + bytes + 4) > malloclimit)
		return NULL;

	mem = (void *)malloc(bytes + 4);

	if (mem) {
		*mem = bytes;
		mem++;
		bytesmalloced += bytes + 4;
	}

	return mem;
}

void
Limited_free(void *ptr)
{
	register ULONG *p;

	p = ptr;
	if (p) {
		/* backup to get size */
		p--;

		/* count the memory as freed */
		bytesmalloced -= *p + 4;

		/* free the memory */
		free(mypool,p);
	}
}

#if 0
void
Limited_MemCleanup()
{
	if (mypool) {
		DeletePool(mypool);
		mypool = NULL;
	}
}
#endif
#endif

#endif /* FSE */
