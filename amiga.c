/*	AMIGA:	Various amiga-specific routines for MicroEMACS */

#include	<stdio.h>
#include	"estruct.h"
#include	"edef.h"

#if AMIGA

#include 	<proto/intuition.h>
#include 	<proto/exec.h>
#include 	<proto/dos.h>
#include 	<proto/asl.h>
#include	<dos/dos.h>
#include	<dos/dosextens.h>


#ifdef __SASC_60
#pragma tagcall AslBase AllocAslRequestTags 30 8002
#pragma tagcall AslBase AslRequestTags 3C 9802
#endif

struct IntuitionBase *IntuitionBase;
struct Library *AslBase;
struct Window *conwin;

struct Window *GetWin(BPTR fh);
char *FReq(char *title, char *buf, int nbuf);

// font size
int fontx = 8, fonty = 8;

// window size
int amwinh, amwinw;

APTR freq = NULL;


void
AmigaInit(BPTR fh)
{
	IntuitionBase = (struct IntuitionBase *)
		OpenLibrary("intuition.library", 37L);
	if (IntuitionBase) {
		AslBase = OpenLibrary("asl.library", 37L);
		if (AslBase) {
		        // we want close gadget reports
        		Write(fh, "\x9B" "11;12;21;2{", 12);
        	
         		conwin = GetWin(fh);
	         	if (conwin) {
				fonty = conwin->RPort->TxHeight;
				fontx = conwin->RPort->TxWidth;
			
				dosizing();
				
				InitFReq();
        	 	}
        	}
        }
}

int
doevent(int evno)
{
	char buf[8], p = buf;
	int i, c;
	
	switch(evno) {
	case 2:
		// snapshot mouse coords & time here
		
		/* eat characters until ';' */
		while (tgetc() != ';')
			;
		/* get num */
		while ((c = tgetc()) != ';')
			*p++ = c;
		*p = '\0';
		i = atoi(buf);
		
		/* eat characters until '|' */
		while (tgetc() != '|')
			;
		
		break;
	case 11:
		/* eat characters until '|' */
		while (tgetc() != '|')
			;
		return(SPEC | 'c');
	case 21:
		if (conwin) {
			if ((conwin->Width == amwinw)
			&&  (conwin->Height == amwinh)) {
				while (tgetc() != '|')
					;

				return(SPEC | 'w');
			}
								
			amwinw = conwin->Width;
			amwinh = conwin->Height;
		}
	case 12:
		while (tgetc() != '|')
			;
		/* eat characters until '|' */
		dosizing();
		return(SPEC | 'w');
	default:
		while (tgetc() != '|')
			;
		return(SPEC | 'u');
	}
}


void
AmigaCleanup(BPTR fd)
{
	FreeFReq();
	
	if (AslBase) {
		CloseLibrary((struct Library *)AslBase);
		AslBase = NULL;
	}
	if (IntuitionBase) {
		CloseLibrary((struct Library *)IntuitionBase);
		IntuitionBase = NULL;
	}
}


struct Window *
GetWin(BPTR fh)
{
	struct FileHandle *fhx;
	struct StandardPacket __aligned spak;
	struct InfoData __aligned idat;
	struct Process *proc;
	struct Window *win;
	long result;
	
	fhx = (struct FileHandle *)(fh<<2);
	proc = (struct Process *)FindTask(NULL);

	spak.sp_Msg.mn_Node.ln_Name	= (char *)&(spak.sp_Pkt);
	spak.sp_Pkt.dp_Link		= &spak.sp_Msg;
	spak.sp_Pkt.dp_Port		= &proc->pr_MsgPort;
	spak.sp_Pkt.dp_Type		= ACTION_DISK_INFO;
	spak.sp_Pkt.dp_Arg1		= (BPTR)(((ULONG)(&idat)) >> 2);
	
	PutMsg(fhx->fh_Type, (struct Message *)&spak);
	WaitPort(&proc->pr_MsgPort);
	GetMsg(&proc->pr_MsgPort);
	
	result = spak.sp_Pkt.dp_Res1;
	win = (struct Window *)idat.id_VolumeNode;
	
	if (!result)
		return NULL;
		
	return(win);
}


dosizing()
{
	int r, c;
	
	amwinw = conwin->Width;
	amwinh = conwin->Height;
	
	c = (conwin->Width - conwin->BorderLeft
			- conwin->BorderRight) / fontx;
	r = (conwin->Height - conwin->BorderTop
			- conwin->BorderBottom) / fonty;
			
	if (r > term.t_mrow)
		r = term.t_mrow;

	if (c > term.t_mcol)
		c = term.t_mcol;
		
	newsize(TRUE, r);
	newwidth(TRUE, c);
}


aboutreq(int f, int n)
{
	struct EasyStruct es = {
		sizeof(struct EasyStruct),
		0,
		PROGNAME " " VERSION " Amiga",

		"     By Ty Sarna, <tsarna@endicor.com>\n"
		"Copyright © 1993 Endicor Technologies, Inc.\n"
		"           All Rights Reserved.\n"
		"\n"
		"                 Based on:\n"
		"          MicroEMACS 3.9 & 3.11c\n"
		"        Written by Dave G. Conroy.\n"
		" Modified by Steve Wilhite, George Jones.\n"
		"Substantially modified by Daniel Lawrence.\n"
		" Copyright © 1987 by Daniel M. Lawrence.",
		
		"OK"
	};
	
	if (conwin) {
		EasyRequestArgs(conwin, &es, NULL, NULL);
	}
	
	return(TRUE);
}



askquickexit(int f, int n)
{
	struct EasyStruct es = {
		sizeof(struct EasyStruct),
		0,
		PROGNAME " " VERSION " Amiga",
		"Save changed files and exit?",
		"OK|CANCEL"
	};
	
	if (conwin) {
		if (EasyRequestArgs(conwin, &es, NULL, NULL)) {
			return quickexit(f, n);
		} else {
			return(TRUE);
		}
	} else {
		return quickexit(f, n);
	}
}


int
ifmlreply(char *prompt, char *buf, int nbuf)
{
	char pbuf[64];
	
	if (clexec || !freq) {
		return(nextarg(prompt, buf, nbuf, ctoec('\n')));
	} else {
		if (filereq) {
			return FReq(prompt, buf, nbuf);
		} else {
			sprintf(pbuf, "[\"?\" for file requester] %s", prompt);
			if (nextarg(pbuf, buf, nbuf, ctoec('\n'))) {
				if (!strcmp(buf, "?")) {
					return FReq(prompt, buf, nbuf);
				} else {
					return TRUE;
				}
			} else {
				return FALSE;
			}
		}
	}
}
        	

char *
FReq(char *title, char *buf, int nbuf)
{
	if (AslRequestTags(freq, ASLFR_TitleText, title, TAG_DONE)) {
		strncpy(buf, ((struct FileRequester *)freq)->fr_Drawer, nbuf);
		AddPart(buf, ((struct FileRequester *)freq)->fr_File, nbuf);
		
		return TRUE;
	} else {
		return FALSE;
	}
}


InitFReq()
{
	if (conwin) {
		freq = AllocAslRequestTags(ASL_FileRequest,
			ASLFR_Window,		conwin,
			ASLFR_SleepWindow,	TRUE,
			ASLFR_DoPatterns,	TRUE,
			ASLFR_RejectPattern,	"#?.info",
		
			TAG_DONE
		);
	}
}


FreeFReq()
{
	if (freq) {
		FreeAslRequest(freq);
		freq = FALSE;
	}
}


#endif
