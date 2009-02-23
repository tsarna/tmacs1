/*
 * This file contains the command processing functions for BBX.
 */

#include        <stdio.h>
#include	"estruct.h"
#include        "edef.h"

#if FSE

#include 	"bbxbase.h"
#include 	"bbxshell.h"
#include 	"bbxdefines.h"

extern struct CallBack *CB;

extern int ifile();

extern int sysop;



bbx_ask_proto(f, n)
{
	SetMaybeAskMore(0);
	CLS();

	Menu_Command(58, "");
	
	/* force screen redraw */
	sgarbf = TRUE;
	
        return (TRUE);
}



bbx_conference(f, n)
{
	SetMaybeAskMore(0);
	CLS();

	Menu_Command(62, "");
	
	/* force screen redraw */
	sgarbf = TRUE;
	
        return (TRUE);
}



bbx_send_nodemsg(f, n)
{
	SetMaybeAskMore(0);
	CLS();

	DoNodeMenu();
	
	SetMaybeAskMore(0);
	CLS();

	/* force screen redraw */
	sgarbf = TRUE;
	
        return (TRUE);
}



bbx_upload_insert(f, n)
{
	char buf[128];
	int result;
	
	SetMaybeAskMore(0);
	CLS();

	sprintf(buf, "BBX:Usr/%s/emacstmp-uli", CB->UL->Name);
	ProtocolReceive(buf, FALSE);

	AskMore();	
	SetMaybeAskMore(0);
	CLS();

	result = ifile(buf);	

	unlink(buf);
	

	/* force screen redraw */
	sgarbf = TRUE;
	
        return (result);
}


#endif
