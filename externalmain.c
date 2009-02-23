#include "estruct.h"

#if FSE
/*
 * Public startup module to be linked in with all BBX Shell modules.
 *
 * externalmain.c,v 1.1.1.1 1993/10/22 18:55:10 tsarna Exp
 * /endicor.com/src/tmacs/externalmain.c,v 
 *
 */

#include <exec/types.h>
#include "bbxdefines.h"
#include "bbxshell.h"

#undef DEBUG

void CBSetup(void);
int atoi(char *a);
int MainLoop(int argc, char **argv);

extern struct DOSBase *DOSBase;
struct CallBack *CB;
struct UserLog *User;
struct BBXBase *BBXBase;
struct NodeIdent *NI;

void (*getLine)(char *buffer, int length, int type);
void (*oLine)(char *);
int (*iChar)(void);
int (*iReady)(void);
void (*Done)(void);
int (*TimeLeft)(void);
int (*UserGone)(void);
void (*Prompt)(char *Text, char *Buffer, int Length, int Type);
int (*CheckNodeMessages)(int);
void (*Chat)(void);
void (*SetNodeLocation)(char *);
int (*GetChar)(void);
void (*oLineRaw)(char *);
void (*CLS)(void);
void (*EventProcess)(void);
void (*SetMaybeAskMore)(int State);
char *(*TextEdit)(char *, int);
int (*FormatText)(char *, int);
int (*ProtocolSend)(char *fname, int DoStats);
int (*ProtocolReceive)(char *fname, int DoStats);
void (*Translate)(char *Txt);

void (*DisableNodeMessages)(void);
void (*EnableNodeMessages)(void);
int (*PrintNodeMessages)(void);
int (*CheckForAbort)(void);
int (*AskMore)(void);
void (*oFile)(char *fname);
void (*oFileTranslated)(char *fname);
int (*Menu_Command)(int Num, char *commandline);

void (*Invalidate_VirTerm)(struct VirTerm *VT);
void (*Free_VirTerm)(struct VirTerm *VT);
struct VirTerm *(*Init_VirTerm)(int xsize, int ysize, char *ColourMap);
void (*Update_VirTerm)(struct VirTerm *VT, char *BuffPtr, int BufLenNear, int (*OutputFunc)(char *Data, int Len));
void (*PrintAt_VirTerm)(struct VirTerm *VT, int xpos, int ypos, char *TheText, int FGCol, int BGCol, int Attribs);
void (*DrawBox_VirTerm)(struct VirTerm *VT, int left, int top, int right, int bottom, int BorderType, unsigned char BorderCol, unsigned char InteriorCol);

int (*GetCharRaw)(void);


void
CBSetup(void)
{
User = CB->UL;
BBXBase=CB->BBXBase;
NI=CB->NI;

getLine = CB->getLine;
oLine = CB->oLine;
iChar = CB->iChar;
iReady = CB->iReady;
Done = CB->Done;
TimeLeft = CB->TimeLeft;
UserGone = CB->UserGone;
Prompt = CB->Prompt;
CheckNodeMessages = CB->CheckNodeMessages;
Chat = CB->Chat;
SetNodeLocation = CB->SetNodeLocation;
GetChar=CB->GetChar;
oLineRaw=CB->oLineRaw;
CLS=CB->CLS;
EventProcess=CB->EventProcess;
SetMaybeAskMore=CB->SetMaybeAskMore;
TextEdit=CB->TextEdit;
FormatText=CB->FormatText;
ProtocolSend=CB->ProtocolSend;
ProtocolReceive=CB->ProtocolReceive;
Translate=CB->Translate;

DisableNodeMessages=CB->DisableNodeMessages;
EnableNodeMessages=CB->EnableNodeMessages;
PrintNodeMessages=CB->PrintNodeMessages;
CheckForAbort=CB->CheckForAbort;
AskMore=CB->AskMore;
oFile=CB->oFile;
oFileTranslated=CB->oFileTranslated;
Menu_Command=CB->Menu_Command;
Invalidate_VirTerm=CB->Invalidate_VirTerm;
Free_VirTerm=CB->Free_VirTerm;
Init_VirTerm=CB->Init_VirTerm;
Update_VirTerm=CB->Update_VirTerm;
PrintAt_VirTerm=CB->PrintAt_VirTerm;
DrawBox_VirTerm=CB->DrawBox_VirTerm;

GetCharRaw=CB->GetCharRaw;
}

int
main(int argc, char **argv)
{
if (argc<2) return;
CB = (struct CallBack *)atoi(argv[1]);
CBSetup();

MainLoop(argc, argv);
Done();
return(0);
}
#endif
