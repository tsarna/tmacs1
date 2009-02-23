/*
 * The BBX Shell interface prototypes and CallBack structure.
 *
 * bbxshell.h,v 1.1.1.1 1993/10/22 18:55:07 tsarna Exp
 * /endicor.com/src/tmacs/bbxshell.h,v 
 *
 */

#ifndef BBX_SHELL_H
#define BBX_SHELL_H

#include <stdio.h>
#include <exec/types.h>

#define INTERFACE_VERSION	0x101

struct CallBack
	{
	void *getLine;		// Get a line of text
	void *oLine;		// Output a string of text
	void *iChar;		// Get a single character
	void *iReady;		// Is there some input ready?
	void *Done;		// He's done, and he's quitting
	void *TimeLeft;		// Time in minutes remaining
	void *UserGone;		// Boolean - is he still here?
	struct NodeIdent *NI;	// The BBX NodeIdent
	struct UserLog *UL;	// The current User
	struct BBX_Config *BBC;	// The current node configuration
	struct BBXBase *BBXBase;// So he won't have to open it
	void *Prompt;		// Prompt routine...
	void *CheckNodeMessages; // Check for any waiting node messages,
				// and print them, returning NonZero if any
				// were printed
	void *Chat;		// The system Chat routine.
	void *SetNodeLocation;	// Change this node's NodeIdent location
	void *GetChar;		// Get a character, or NULL, no waiting
	void *oLineRaw;		// Output the text with NO processing.
	void *CLS;		// Clear the user's screen, based on his
				// preferences (may do nothing) and ask MORE
				// if deemed necessary.
	void *EventProcess;	// Check Intuition MsgPorts and other MsgPorts
				// Regularly!

	ULONG BBXVersion;	// Version # of BBX
	ULONG InterfaceVersion;	// Version # of the Shell interface

	void *SetMaybeAskMore;	// Change the MaybeAskMore flag.
	void *TextEdit;		// Invoke the BBX message editor
	void *FormatText;	// Output text formatted
	void *ProtocolSend;	// Send file via binary transfer (Zmodem,Xmodem)
	void *ProtocolReceive;	// Send file via binary transfer (Zmodem,Xmodem)
	void *Translate;	// Transmit translating backslash codes

	void *DisableNodeMessages;	// Disable Node Message Printing
	void *EnableNodeMessages;	// Enable node message printing
	void *PrintNodeMessages;	// Print pending node messages
	void *CheckForAbort;	// Check for abort, print [Aborted] msg if so
	void *AskMore;		// Do a More prompt
	void *oFile;		// Output a file, raw
	void *oFileTranslated;	// Output a file, with backslash translation
	void *Menu_Command;	// Call a BBXMENU number

	void *Init_VirTerm;		// Initialize a new virtual terminal
	void *Free_VirTerm;		// Deallocate a virtual terminal
	void *Invalidate_VirTerm;	// Clear a virtual terminal
	void *Update_VirTerm;		// Refresh the virtual terminal
	void *PrintAt_VirTerm;		// Print to a position in the vterm
	void *DrawBox_VirTerm;		// Draw an ASCII box

	// Functions new to Version 0x101
	void *GetCharRaw;		// Get a character, no CSI processing
	};

#ifndef BBX_PROPER
extern struct CallBack *CB;			// Set by externalmain.c
extern struct UserLog *User;
extern struct BBXBase *BBXBase;
extern struct NodeIdent *NI;

extern void (*getLine)(char *buffer, int length, int type);
extern void (*Prompt)(char *Text, char *Buffer, int Length, int Type);
extern int (*iChar)(void);
extern int (*iReady)(void);
extern void (*Done)(void);
extern int (*TimeLeft)(void);
extern int (*UserGone)(void);
extern void (*Chat)(void);
extern int (*CheckNodeMessages)(int);
extern void (*SetNodeLocation)(char *);
extern int (*GetChar)(void);
extern void (*oLineRaw)(char *);
extern void (*CLS)(void);
extern void (*EventProcess)(void);
extern void (*SetMaybeAskMore)(int State);
extern char *(*TextEdit)(char *, int);
extern int (*FormatText)(char *, int);
extern int (*ProtocolSend)(char *fname, int DoStats);
extern int (*ProtocolReceive)(char *fname, int DoStats);
extern void (*Translate)(char *Txt);

extern void (*DisableNodeMessages)(void);
extern void (*EnableNodeMessages)(void);
extern int (*CheckForAbort)(void);
extern int (*AskMore)(void);
extern void (*oFile)(char *fname);
extern int (*PrintNodeMessages)(void);
extern void (*oFileTranslated)(char *fname);
extern int (*Menu_Command)(int Num, char *commandline);

extern void (*Invalidate_VirTerm)(struct VirTerm *VT);
extern void (*Free_VirTerm)(struct VirTerm *VT);
extern struct VirTerm *(*Init_VirTerm)(int xsize, int ysize, char *ColourMap);
extern void (*Update_VirTerm)(struct VirTerm *VT, char *BuffPtr, int BufLenNear, int (*OutputFunc)(char *Data, int Len));
extern void (*PrintAt_VirTerm)(struct VirTerm *VT, int xpos, int ypos, char *TheText, int FGCol, int BGCol, int Attribs);
extern void (*DrawBox_VirTerm)(struct VirTerm *VT, int left, int top, int right, int bottom, int BorderType, unsigned char BorderCol, unsigned char InteriorCol);

extern int (*GetCharRaw)(void);

#ifndef SKIP_OLINE
extern void (*oLine)(char *);		// Shadow has it's own oLine
#endif

#endif
#endif
