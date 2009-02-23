/*	EBIND:		Initial default key to function bindings for
			MicroEMACS 3.9
*/

/*
 * Command table.
 * This table  is *roughly* in ASCII order, left to right across the
 * characters of the command. This explains the funny location of the
 * control-X commands.
 */
KEYTAB  keytab[NBINDS] = {
	{Ctrl|'A',		gotobol},
	{Ctrl|'B',		backchar},
	{Ctrl|'C',		insspace},
	{Ctrl|'D',		forwdel},
	{Ctrl|'E',		gotoeol},
	{Ctrl|'F',		forwchar},
	{Ctrl|'G',		ctrlg},
	{Ctrl|'H',		backdel},
	{Ctrl|'I',		tab},
	{Ctrl|'J',		indent},
	{Ctrl|'K',		killtext},
	{Ctrl|'L',		refresh},
	{Ctrl|'M',		newline},
	{Ctrl|'N',		forwline},
	{Ctrl|'O',		openline},
	{Ctrl|'P',		backline},
	{Ctrl|'Q',		quote},
	{Ctrl|'R',		backsearch},
	{Ctrl|'S',		forwsearch},
	{Ctrl|'T',		twiddle},
	{Ctrl|'U',		unarg},
	{Ctrl|'V',		forwpage},
	{Ctrl|'W',		killregion},
	{Ctrl|'X',		cex},
	{Ctrl|'Y',		yank},
	{Ctrl|'Z',		backpage},
	{Ctrl|']',		metakey},
	{Ctrl|']',		searchterm},
	{CTLX|Ctrl|'B',		listbuffers},
	{CTLX|Ctrl|'C',		quit},          /* Hard quit.           */
#if	AEDIT
	{CTLX|Ctrl|'D',		detab},
	{CTLX|Ctrl|'E',		entab},
#endif
	{CTLX|Ctrl|'F',		filefind},
	{CTLX|Ctrl|'I',		insfile},
	{CTLX|Ctrl|'L',		lowerregion},
	{CTLX|Ctrl|'M',		delmode},
	{CTLX|Ctrl|'N',		mvdnwind},
	{CTLX|Ctrl|'O',		deblank},
	{CTLX|Ctrl|'P',		mvupwind},
	{CTLX|Ctrl|'R',		fileread},
	{CTLX|Ctrl|'S',		filesave},
#if	AEDIT
	{CTLX|Ctrl|'T',		trim},
#endif
	{CTLX|Ctrl|'U',		upperregion},
	{CTLX|Ctrl|'V',		viewfile},
	{CTLX|Ctrl|'W',		filewrite},
	{CTLX|Ctrl|'X',		swapmark},
	{CTLX|Ctrl|'Z',		shrinkwind},
	{CTLX|'?',		deskey},
	{CTLX|'!',		spawn},
	{CTLX|'@',		pipecmd},
	{CTLX|'#',		filter},
	{CTLX|'=',		showcpos},
	{CTLX|'(',		ctlxlp},
	{CTLX|')',		ctlxrp},
	{CTLX|'^',		enlargewind},
	{CTLX|'0',		delwind},
	{CTLX|'1',		onlywind},
	{CTLX|'2',		splitwind},
	{CTLX|'A',		setvar},
	{CTLX|'B',		usebuffer},
#if	BSD
	{CTLX|'D',		bktoshell},
#endif
        {CTLX|'E',              ctlxe},
	{CTLX|'F',		setfillcol},
	{CTLX|'K',		killbuffer},
	{CTLX|'M',		setmode},
	{CTLX|'N',		filename},
	{CTLX|'O',		nextwind},
	{CTLX|'P',		prevwind},
#if	ISRCH
	{CTLX|'R',		risearch},
	{CTLX|'S',		fisearch},
#endif
	{CTLX|'W',		resize},
	{CTLX|'X',		nextbuffer},
	{CTLX|'Z',		enlargewind},
#if	WORDPRO
	{META|Ctrl|'C',		wordcount},
#endif
#if	PROC
	{META|Ctrl|'E',		execproc},
#endif
#if	CFENCE
	{META|Ctrl|'F',		getfence},
#endif
	{META|Ctrl|'H',		delbword},
	{META|Ctrl|'K',		unbindkey},
	{META|Ctrl|'L',		reposition},
	{META|Ctrl|'M',		delgmode},
	{META|Ctrl|'N',		namebuffer},
	{META|Ctrl|'R',		qreplace},
#if	CTAGS
	{META|Ctrl|'T',		backtagword},
#endif
	{META|Ctrl|'V',		scrnextdw},
#if	WORDPRO
	{META|Ctrl|'W',		killpara},
#endif
	{META|Ctrl|'Z',		scrnextup},
	{META|' ',		setmark},
	{META|'?',		help},
	{META|'!',		reposition},
	{META|'.',		setmark},
	{META|'>',		gotoeob},
	{META|'<',		gotobob},
	{META|'~',		unmark},
#if	APROP
	{META|'A',		apro},
#endif
	{META|'B',		backword},
	{META|'C',		capword},
	{META|'D',		delfword},
#if	CRYPT
	{META|'E',		setkey},
#endif
	{META|'F',		forwword},
	{META|'G',		gotoline},
	{META|'K',		bindtokey},
	{META|'L',		lowerword},
	{META|'M',		setgmode},
#if	WORDPRO
	{META|'N',		gotoeop},
	{META|'P',		gotobop},
	{META|'Q',		fillpara},
#endif
	{META|'R',		sreplace},
#if	CTAGS
	{META|'T',		tagword},
#endif
	{META|'U',		upperword},
	{META|'V',		backpage},
	{META|'W',		copyregion},
	{META|'X',		namedcmd},
	{META|'Z',		quickexit},
	{META|0x7F,             delbword},

#if	MSDOS
	{SPEC|Ctrl|'_',		forwhunt},
	{SPEC|Ctrl|'S',		backhunt},
	{SPEC|71,		gotobob},
	{SPEC|72,		backline},
	{SPEC|73,		backpage},
	{SPEC|75,		backchar},
	{SPEC|77,		forwchar},
	{SPEC|79,		gotoeob},
	{SPEC|80,		forwline},
	{SPEC|81,		forwpage},
	{SPEC|82,		insspace},
	{SPEC|83,		forwdel},
	{SPEC|115,		backword},
	{SPEC|116,		forwword},
#if	WORDPRO
	{SPEC|132,		gotobop},
	{SPEC|118,		gotoeop},
#endif
	{SPEC|84,		cbuf1},
	{SPEC|85,		cbuf2},
	{SPEC|86,		cbuf3},
	{SPEC|87,		cbuf4},
	{SPEC|88,		cbuf5},
	{SPEC|89,		cbuf6},
	{SPEC|90,		cbuf7},
	{SPEC|91,		cbuf8},
	{SPEC|92,		cbuf9},
	{SPEC|93,		cbuf10},
#endif

#if	TERMCAP
	{SPEC|'A',		backline},
	{SPEC|'B',		forwline},
	{SPEC|'C',		forwchar},
	{SPEC|'D',		backchar},
#endif

#if	AMIGA
	{SPEC|'?',		help},
	{SPEC|'A',		backline},
	{SPEC|'B',		forwline},
	{SPEC|'C',		forwchar},
	{SPEC|'D',		backchar},
	{SPEC|'T',		backpage},
	{SPEC|'S',		forwpage},
	{SPEC|'a',		backword},
	{SPEC|'`',		forwword},
	{SPEC|'c',		quickexit},
	{SPEC|'w',		nullproc},
	{SPEC|'P',		cbuf1},
	{SPEC|'Q',		cbuf2},
	{SPEC|'R',		cbuf3},
	{SPEC|'S',		cbuf4},
	{SPEC|'T',		cbuf5},
	{SPEC|'U',		cbuf6},
	{SPEC|'V',		cbuf7},
	{SPEC|'W',		cbuf8},
	{SPEC|'X',		cbuf9},
	{SPEC|'Y',		cbuf10},
	{127,			forwdel},
#endif

	{0x7F,			backdel},

	/* special internal bindings */
	SPEC|META|'W',		wrapword,	/* called on word wrap */
	SPEC|META|'C',		nullproc,	/*  every command input */
	SPEC|META|'R',		nullproc,	/*  on file read */
	SPEC|META|'O',		viewmode,	/* open read-only file  */
	{0,			NULL}
};

#if RAINBOW

#include "rainbow.h"

/*
 * Mapping table from the LK201 function keys to the internal EMACS character.
 */

short lk_map[][2] = {
	Up_Key,                         Ctrl+'P',
	Down_Key,                       Ctrl+'N',
	Left_Key,                       Ctrl+'B',
	Right_Key,                      Ctrl+'F',
	Shift+Left_Key,                 META+'B',
	Shift+Right_Key,                META+'F',
	Control+Left_Key,               Ctrl+'A',
	Control+Right_Key,              Ctrl+'E',
	Prev_Scr_Key,                   META+'V',
	Next_Scr_Key,                   Ctrl+'V',
	Shift+Up_Key,                   META+'<',
	Shift+Down_Key,                 META+'>',
	Cancel_Key,                     Ctrl+'G',
	Find_Key,                       Ctrl+'S',
	Shift+Find_Key,                 Ctrl+'R',
	Insert_Key,                     Ctrl+'Y',
	Options_Key,                    Ctrl+'D',
	Shift+Options_Key,              META+'D',
	Remove_Key,                     Ctrl+'W',
	Shift+Remove_Key,               META+'W',
	Select_Key,                     Ctrl+'@',
	Shift+Select_Key,               CTLX+Ctrl+'X',
	Interrupt_Key,                  Ctrl+'U',
	Keypad_PF2,                     META+'L',
	Keypad_PF3,                     META+'C',
	Keypad_PF4,                     META+'U',
	Shift+Keypad_PF2,               CTLX+Ctrl+'L',
	Shift+Keypad_PF4,               CTLX+Ctrl+'U',
	Keypad_1,                       CTLX+'1',
	Keypad_2,                       CTLX+'2',
	Do_Key,                         CTLX+'E',
	Keypad_4,                       CTLX+Ctrl+'B',
	Keypad_5,                       CTLX+'B',
	Keypad_6,                       CTLX+'K',
	Resume_Key,                     META+'!',
	Control+Next_Scr_Key,           CTLX+'N',
	Control+Prev_Scr_Key,           CTLX+'P',
	Control+Up_Key,                 CTLX+Ctrl+'P',
	Control+Down_Key,               CTLX+Ctrl+'N',
	Help_Key,                       CTLX+'=',
	Shift+Do_Key,                   CTLX+'(',
	Control+Do_Key,                 CTLX+')',
	Keypad_0,                       CTLX+'Z',
	Shift+Keypad_0,                 CTLX+Ctrl+'Z',
	Main_Scr_Key,                   Ctrl+'C',
	Keypad_Enter,                   CTLX+'!',
	Exit_Key,                       CTLX+Ctrl+'C',
	Shift+Exit_Key,                 Ctrl+'Z'
};

#define lk_map_size     (sizeof(lk_map)/2)
#endif

