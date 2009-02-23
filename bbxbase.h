/*
 * The BBX.library base and prototypes.
 *
 * bbxbase.h,v 1.1.1.1 1993/10/22 18:55:07 tsarna Exp
 * /endicor.com/src/tmacs/bbxbase.h,v 
 *
 */

#ifndef BBX_BASE_H
#define BBX_BASE_H

#include <exec/types.h>
#include <exec/lists.h>
#include <exec/libraries.h>
#include <exec/semaphores.h>

/** Node Stuff **/

#define NS_WAITING 	0		/* Nobody online */
#define NS_ACTIVE 	1		/* He's here! */
#define NS_BUSY		2		/* He's here, but he's busy */

#define REQ_QUITNOW	(1<<0)		/* Boot user off IMMEDIATELY */
#define REQ_QUITASAP	(1<<1)		/* Boot user off within 2 minutes */
#define REQ_QUITSOON	(1<<2)		/* Let user leave when he pleases */
#define REQ_CONFNOTIFY	(1<<3)		/* Notify me when people arrive/leave */
#define REQ_NOMESSAGES	(1<<4)		/* Don't send me unimportant messages */

#define GNS_SHORT	0
#define GNS_LONG	1

struct NodeMessage
	{
	struct NodeMessage *Next;
	char Text[1];			// Extends from here
	};

struct NodeIdent		// described in bbx.shell.docs
	{	
	struct NodeIdent *Next;
	short NodeNum;
	short NodeState;		/* see NS_#? above */
	char IDString[60];
	char UserName[64];
	char UserFrom[32];
	struct UserLog *UE;
	struct NodeMessage *MessageWaiting;
	ULONG CurrentBaud;
	char ConfHandle[15];
	char ConfChannel;			/* If -1, he's not in Conf */
	short Requests;				/* Bits - See above */
	char  NodeLocation[62];			/* "Reading Messages" */
	};

/** Structure for the Lock List **/

struct LockNode
	{
	struct LockNode *Next;
	char *LockName;
	struct SignalSemaphore Semaphore;
	};


/** The BBX Library Base **/

struct BBXBase 
	{
	struct Library LibNode;
	UBYTE  Flags;
	UBYTE  pad;

	/* We are now longword aligned */
	ULONG  SysLib;
	ULONG  DosLib;
	ULONG  SegList;

	/* Various BBX Library semaphores */
	struct SignalSemaphore *MsgHeadLock;
	struct SignalSemaphore *MsgTextLock;
	struct SignalSemaphore *NodeListLock;
	struct SignalSemaphore *LockListLock;

	/* Library-Base stuff that you ARE allowed to read */
	struct SysInfo *SysInfo;
	struct NodeIdent *NodeList;
	
	/* BBX-Specific stuff - PRIVATE - DO NOT READ - USE FUNCTIONS! */
	ULONG  volatile LowMessage;
	ULONG  volatile HighMessage;
	ULONG  volatile NumMessages;
	struct LockNode *LockList;	// AttemptItem() Lock List

	ULONG LockCount;
	};

#define BBXLIB_VERSION	3
#define BBXLIB_REVISION	1

#define MAF_EXCLUSIVE	(1<<0)

#ifdef LATTICE
#define BITS unsigned int
#endif


/**********************************************************************/
/*           BBX Library Function Prototypes and Autodocs?            */
/**********************************************************************/

/* * Returns the size of the given file - that's it * */
long FileSize(char *name);

/* * Allocates and Reads the message.  Takes the MsgNum, and fills in
     the MsgHead (MH) and the Buffer (8K Max). Flags is currently unused.
     NOTE: Returns 0 if no such msg, 1 if LOCKED, -1 if success * */

int ObtainMessage(ULONG MsgNum, struct MsgHead *MH, char *Buffer, USHORT Flags);

/* * Release a message obtained with ObtainMessage - No Flags * */
void ReleaseMessage(ULONG MsgNum, USHORT Flags);

/* * Add a new message to the BBX Message Base - Gets from 
     MsgHead, fills in the number, fills in the Records, and 
     writes it and the Null-Terminated Buffer.  No flags * */

ULONG CreateMessage(struct MsgHead *MH, char *Buffer, short Flags);

/* * Kill this message from the message base.  Returns success. * */
int DeleteMessage(ULONG MsgNum, USHORT Flags);

/* * Takes nothing, returns nothing. * */
void unused(void);

/* * Returns the number of the lowest message in the message base * */
ULONG GetLowMessage(void);

/* * Returns the number of the highest message in the message base * */
ULONG GetHighMessage(void);

/* * Returns the number of callers BBX has had. * */
ULONG GetNumCallers(void);

/* * Sets the number of callers BBX has had. * */
void SetNumCallers(ULONG);

/* * Register a new node with the library - makes this node available
     to any node reading the node list, etc. * */

int AddNode(struct NodeIdent *NI);

/* * Remove a node from the BBX node list.  Must happen before you quit * */
void RemoveNode(struct NodeIdent *NI);

/* * Write any data in any buffers out to disk.  Takes a few seconds * */
void FlushData(void);

/* * Attempts to get the header of MsgNum (no flags).  Returns success * */
int GetMessageHeader(int MsgNum, struct MsgHead *MH, short Flags);

/* * Updates the given message header.  Num is in MH->mh_MsgNum, no flags * */
int UpdateMessageHeader(struct MsgHead *MH, short Flags);


/* * Obtain the "Item" named.  An item is a named semaphore created on
     demand... * */
int ObtainItem(char *ItemName);


/* * Attempt to obtain the named item.  Return success. * */
int AttemptItem(char *ItemName);


/* * Release the item as obtained.  * */
void ReleaseItem(char *ItemName);


/* * Find a particular node, searching by user name * */
struct NodeIdent *GetNodeAddress(char *UserName);


/* * Send a message to a user.  No header or footer is added. * */
void SendNodeMessage(char *MessageString, struct NodeIdent *NodeIdent);

/* * Get text for a message header obtained from GetMessageHeader() * */
ULONG GetMessageText(struct MsgHead *MH, char *Buffer, ULONG Flags);

/* * Gets the named user variable into the passed Buffer * */
int GetUserVariable(char *UserName, char *VarName, char *Buffer, ULONG BufLen);

/* * Sets the named user variable for the named user * */
int SetUserVariable(char *UserName, char *VarName, char *VarText);

/* * Returns the number of active messages in the message base * */
ULONG GetActiveMessages(void);

/* * Locks BBXBase - nobody else can open it while it's locked * */
ULONG LockBBXLibrary(void);

/* * Unlocks BBXBase one level - Locks can nest * */
void UnlockBBXLibrary(void);

/* * Frees BBX library resources.  Internal use only! * */
void FreeLibraryResources(void);

/* * Reopens BBX library resources.  Internal use only! * */
ULONG ReopenLibraryResources(void);

#include "bbxlib.h"

#endif /* BBX_BASE_H */

