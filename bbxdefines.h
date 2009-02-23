/*
 * BBX Master definitions (Public)
 *
 * bbxdefines.h,v 1.1.1.1 1993/10/22 18:55:07 tsarna Exp
 * /endicor.com/src/tmacs/bbxdefines.h,v 
 *
 */

#ifndef BBX_DEFINES_H
#define BBX_DEFINES_H


#include <libraries/dos.h>
#include <exec/types.h>

typedef char boolean;

#define NUM_USER_CLASSES	8
#define NUM_MSG_SECTIONS	64
#define NUM_FILE_SECTIONS	64
#define NUM_TERMINAL_TYPES	16

//	Input types that can be passed to getLine() and Prompt()

#define GET_NORMAL 	0	// Basic get string
#define GET_CAPS 	1	// Convert all alpha chars to upper case
#define GET_INT 	2	// Only take numbers.
#define GET_YESNO 	3	// Take only YES or NO, if just return do YES
#define GET_CONTINUE 	4 	// Same as YESNO but also takes 'c' for Continue
#define GET_WRAP 	5	// Do wordwrap at EOL, next GET_WRAP gets
				// the wrapped text.  For multiline input.
#define GET_HIDE 	6	// Don't show what the user types
#define GET_NAME 	7 	// Fix up case STEVE TIBBETT->Steve Tibbett
#define GET_CHAIN 	8	// Use this in menus for ; chaining
#define GET_NOYES 	9	// Same as YESNO but assumes NO on return
#define GET_NORMMSGS	10	// GET_NORMAL but send node messages with !

#define BITS unsigned int	// This may be different on other compilers

#define NUM_SECTIONS 	64	// Number of Message and File Areas

/* 
	The New Security System:

	- 64 Message and File READ and WRITE ACCESS flags for each user
	- 64 Message and File Preference flags for each user
	- 64 "SectionSysop" flags - for File and Message areas.
	- 32 SystemAccess bits, predefined below.
	- 16 PublicUserFlags the Sysop can use
	- 4  16 bit variables the Sysop can use however.
	
	The 'User.sysop' flag is important.  Set it, and ALL other
	security checks go off.  Beware.

*/

// This list must correspond with list in security.c

#define SECURITY(name) (User.SystemAccessFlags&SABIT_##name)
#define CHECKALLOWED(name) if ((User.sysop==0) && (!SECURITY(name))) { AccessDenied(); return(FALSE); };
#define CHECKALLOWEDNR(name) if ((User.sysop==0) && (!SECURITY(name))) { AccessDenied(); return; };

#define SABIT_STATISTICS	(1<<0)		// Any Stats Function
#define SABIT_SETAREANAMES	(1<<1)		// Can he config Areas?		
#define SABIT_MODIFYCONFIG	(1<<2)		// Can he change his setup?	
#define SABIT_CALLERLOG		(1<<3)		// Can he read the Caller Log?	
#define SABIT_ENTERMESSAGE	(1<<4)		// Can he enter messages?	
#define SABIT_READMESSAGES	(1<<5)		// Can he read any messages?	
#define SABIT_DELETEMESSAGE	(1<<6)		// Can he kill messages to him?	
#define SABIT_DOWNLOAD		(1<<7)		// Can he download anything?	
#define SABIT_UPLOAD		(1<<8)		// Can he upload anything? 	
#define SABIT_USERLOG		(1<<9)		// Can he read the UserLog?	
#define SABIT_EDITUSER		(1<<10)		// Can he edit users?		
#define SABIT_EDITSYSINFO	(1<<11)		// Can he read/edit SysInfo?	
#define SABIT_BBSINFO		(1<<12)		// Can he read the BBSInfo?	
#define SABIT_READCATALOG	(1<<13)		// Can he read the Catalog?	
#define SABIT_NEWFILES		(1<<14)		// Can he check for New Files?	
#define SABIT_SEARCHFILES	(1<<15)		// Can he search for files?	
#define SABIT_READASCII		(1<<16)		// Can he read ASCII files?	
#define SABIT_GETUSERINFO	(1<<17)		// Can he Get User Info?	
#define SABIT_APPROVEFILES	(1<<18)		// Can he approve files?	
#define SABIT_CHANGEMENUSET	(1<<19)		// Can he change menu sets?	
#define SABIT_PROTOCOL		(1<<20)		// Can he switch protocols?	

#define SABIT_READNODELIST	(1<<22)		// Can he read the Node List?	
#define SABIT_NODEMESSAGES	(1<<23)		// Can he send node messages?	
#define SABIT_CONFERENCE	(1<<24)		// Can he enter Conf?		
#define SABIT_CONFAREATEN	(1<<25)		// Can he enter conf area 10?	
#define SABIT_FILEATTACH	(1<<26)		// Can he upload messages or file attach? 

/* User Class #0 is what New Users get */
/* Don't change this without changing the SIZE below */

struct OldUserClass
	{
	char ClassName[32];

	ULONG MessageReadAccessFlags[2];	/* 64 Bits worth 	*/

	ULONG MessageWriteAccessFlags[2];	/* 64 Bits worth 	*/

	ULONG FileReadAccessFlags[2];		/* 64 Bits worth	*/
	ULONG FileWriteAccessFlags[2];		/* 64 Bits worth	*/

	ULONG MessageSectionPreferences[2];	/* 64 Bits worth	*/
	ULONG FileSectionPreferences[2];	/* 64 Bits worth	*/

	ULONG MessageSectionSysop[2];		/* 64 Bits worth	*/
	ULONG FileSectionSysop[2];		/* 64 Bits worth	*/

	UBYTE Security;
	UBYTE ClassNum;
	ULONG SystemAccessFlags;

	USHORT SysopDefinedFlags;
	USHORT SysopDefinedVariables[4];

	// Also part of this is the Time limit variables in SysInfo
	};

struct UserClass
	{
	char ClassName[32];

	ULONG MessageReadAccessFlags[2];	/* 64 Bits worth 	*/
	ULONG MessageWriteAccessFlags[2];	/* 64 Bits worth 	*/

	ULONG FileReadAccessFlags[2];		/* 64 Bits worth	*/
	ULONG FileWriteAccessFlags[2];		/* 64 Bits worth	*/

	ULONG MessageSectionPreferences[2];	/* 64 Bits worth	*/
	ULONG FileSectionPreferences[2];	/* 64 Bits worth	*/

	ULONG MessageSectionSysop[2];		/* 64 Bits worth	*/
	ULONG FileSectionSysop[2];		/* 64 Bits worth	*/

	UBYTE Security;
	UBYTE ClassNum;
	ULONG SystemAccessFlags;

	UBYTE Ratio;
	UBYTE TimeLimit;
	};

struct TermType
	{
	char TermName[32];

	BITS Reserved: 28;
	BITS Linefeeds: 1;
	BITS Ansi: 1;
	BITS CLS: 1;
	BITS Unused: 1;		// Was AllowChat

	UBYTE PageWidth;
	UBYTE PageHeight;
	UBYTE MenuSet;
	UBYTE Protocol;
	UBYTE Pad;		// Was DefaultClass
	};

struct Section
	{
	unsigned char SectionName[32];

	BITS Reserved 	: 25;
	BITS FidoNetMail: 1;
	BITS Date 	: 1;
	BITS From 	: 1;
	BITS To   	: 1;
	BITS Subject 	: 1;
	BITS Email 	: 1;
	BITS Obsolete	: 1;
	};

struct MsgHead 
	{
	/* mh_From and mh_To are 48 to support a network address */

	char mh_From[48];		/* Who the msg is from 			*/
					/* If mh_From[0]==0, Record is free	*/
	char mh_To[48];			/* Who it's TO 				*/
	char mh_About[32];		/* Why?					*/

	char mh_MsgArea;		/* What msg area this is in 		*/

	BITS mh_Reserved : 26;
	BITS mh_Sent : 1;		/* Fidonet:  Was this sent?		*/
	BITS mh_FileAttached : 1;	/* Is there a file attached?		*/
	BITS mh_Recieved : 1;		/* Has this message been received?	*/
	BITS mh_Private : 1;		/* Is this message 'Private'?		*/
	BITS mh_Unformatted : 1;	/* Format this message when printing?	*/
	BITS mh_Locked : 1;		/* Can this message scroll off?		*/

	ULONG mh_MsgNum;		/* The msg num the user sees 		*/
	ULONG mh_Previous;		/* Msg this one is a reply to 		*/
	ULONG mh_Replies[5];		/* And the next 5 replies. 		*/
	unsigned short mh_Records[32];	/* Pointer to 32 records, at 		*/
					/* 256 bytes per records = 8K		*/
	struct DateStamp mh_Date;
	char mh_FileAttach[32];		/* Name of attached file (if attached)	*/
					/* Use is reserved if no file attached	*/
	};


struct UserLog 
	{
	char Name[32];			/* 31 chars - filename length 		*/
	char City[32];			/* 31 chars 				*/
	char Password[12];		/* 11 chars, let's say 10 		*/
	char Phone[18];			/* Worst case phone # 			*/
	char Country[12];		/* Country he's from 			*/

	BITS reserved 	: 21;		/* Future Expansion			*/
	BITS locationnotify: 1; 	/* Notify on SetNodeLocation()		*/
	BITS loginnotify: 1;		/* Notify of login/logouts		*/
	BITS hotkeys	: 1;		/* Does he want hot keys?		*/
	BITS autopage 	: 1;		/* Flash screen when he logs in 	*/
        BITS msgcls     : 1;            /* CLS before each message              */
	BITS terse 	: 1;		/* Terse prompts when reading 		*/
	BITS cls 	: 1;		/* Does he want CLS's anywhere? 	*/
	BITS registered : 1;		/* Is he "Registered"? 			*/
	BITS linefeeds 	: 1;		/* Does his term get sent linefeeds?	*/
	BITS sysop 	: 1;		/* Is he a 'Sysop'? 			*/
	BITS ansi 	: 1;		/* Is his terminal 'Ansi'? 		*/

	UBYTE Proficiency;		/* 0=Novice, 1=Regular, 2=Expert 	*/

	struct DateStamp LastCall;
	struct DateStamp DateOfFirstCall;

	UBYTE 	TimeLimit;		/* Time per day 			*/
	UBYTE 	TimeLeftToday;		/* Time left today 			*/
	UBYTE 	FileAreaNum;		/* File area num he last catalogged 	*/
	UBYTE 	Protocol;		/* His file transfer protocol		*/
					// (Starts at 1 for available protocols)
	UBYTE 	Ratio;			/* Ratio works like Ratio:1		*/
	UBYTE 	TerminalType;		/* His terminal type (Index)		*/
	ULONG 	HighMsgRead;		/* Highest message number he's read	*/
	USHORT 	PageWidth, PageHeight;	/* Used for formatting			*/
	ULONG 	TotalTimeOnline;
	USHORT 	TotalUploads;
	USHORT 	TotalDownloads;
	ULONG 	TotalMessages;
	USHORT 	TotalMessagesRead;
	USHORT 	NumberCalls;		/* How many times he has logged in 	*/
	UBYTE 	MsgHeaderFormat;	/* His preferred message header format	*/
	UBYTE 	MenuSet;

	/** Security Info **/

	ULONG MessageReadAccessFlags[2];	/* 64 Bits worth 	*/
	ULONG MessageWriteAccessFlags[2];	/* 64 Bits worth 	*/
	ULONG FileReadAccessFlags[2];		/* 64 Bits worth	*/
	ULONG FileWriteAccessFlags[2];		/* 64 Bits worth	*/
	ULONG MessageSectionPreferences[2];	/* 64 Bits worth	*/
	ULONG FileSectionPreferences[2];	/* 64 Bits worth	*/
	ULONG MessageSectionSysop[2];		/* 64 Bits worth	*/
	ULONG FileSectionSysop[2];		/* 64 Bits worth	*/
	UBYTE Security;				/* For Rexx etc		*/
	UBYTE UserClass;	 	/* May be meaningless - Depends	*/
	ULONG SystemAccessFlags;		/* 32 Bits worth	*/

	USHORT Unused[9];			/* Reserved		*/
	};

struct SysInfo
	{
	struct UserLog DefaultUserEntry;
	struct Section MsgSections[NUM_MSG_SECTIONS];
	struct Section FileSections[NUM_FILE_SECTIONS];
	struct TermType Terminals[NUM_TERMINAL_TYPES];
	struct UserClass UserClasses[NUM_USER_CLASSES];
	ULONG NumCallers;
	ULONG Max_Messages;			// Never Change Max_Messages!
	short SysInfoOkay;			// If Zero, we need FIX.
	};

struct OldSysInfo
	{
	struct UserLog DefaultUserEntry;
	struct Section MsgSections[64];
	struct Section FileSections[64];
	struct TermType Terminals[16];
	struct OldUserClass UserClasses[8];
	ULONG NumCallers;
	unsigned char UserClassTimeLimits[8];
	ULONG Max_Messages;			/* Never Change! */
	short SysInfoOkay;			// If Zero, we need FIX.
	char FileSectionDirNums[64];		// Used to figure what directory
						// files uploaded to a given area
						// should be physically put in.
						// > see note in file.h <
	};

struct CallerLogEntry 
	{
	char Name[32];
	char From[32];
	struct DateStamp LoginTime;
	struct DateStamp LogoutTime;
	ULONG CallerNum;
	USHORT Baud;
	USHORT TerminateType;
	USHORT Uploads;
	USHORT Downloads;
	USHORT MsgsLeft;
	USHORT MsgsRead;
	}; 

#endif
