/*
 * Virtual Terminal structure and definitions.
 *
 * virterm.h,v 1.1.1.1 1993/10/22 18:55:15 tsarna Exp
 * /endicor.com/src/tmacs/virterm.h,v 
 *
 */


struct VirTerm 
	{
	unsigned char *CharMap;
	unsigned char *AttribMap;
	unsigned char *ColourMap;		// Bottom nybble is FG

	unsigned char *PrevCharMap;
	unsigned char *PrevAttribMap;
	unsigned char *PrevColourMap;		// Top nybble is BG

	unsigned char LastAttrib;
	unsigned char LastColour;

	short XSize, YSize;

	char AnsiMap[16];			// Only 8 used for now
	};

#define	ATT_BOLD	(1<<0)
#define ATT_ITALIC	(1<<1)
#define ATT_UNDERSCORE	(1<<2)
#define ATT_INVERSE	(1<<3)
#define ATT_REVERSE	ATT_INVERSE
#define ATT_UNDERLINE	ATT_UNDERSCORE
#define ATT_ITALICS	ATT_ITALIC

#define SINGLE_BOX_TL	0xDA
#define SINGLE_BOX_TR	0xBF
#define SINGLE_BOX_BL	0xC0
#define SINGLE_BOX_BR	0xD9
#define SINGLE_HLINE	0xC4
#define SINGLE_VLINE	0xB3

#define DOUBLE_BOX_TL	0xC9
#define DOUBLE_BOX_TR	0xBB
#define DOUBLE_BOX_BL	0xC8
#define DOUBLE_BOX_BR	0xBC
#define DOUBLE_HLINE	0xCD
#define DOUBLE_VLINE	0xBA

#define DBBT_NONE	0
#define DBBT_IBMSINGLE	1
#define DBBT_IBMDOUBLE	2
#define DBBT_ASCII	3
