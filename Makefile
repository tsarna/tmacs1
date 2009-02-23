PROG=tmacs

LDSTATIC=-static

NOGCCERROR=1
LDADD+=-ltermcap # -lcompat

SRCS=	fileio.c line.c spawn.c display.c window.c basic.c eval.c \
	main.c word.c bind.c random.c buffer.c exec.c input.c region.c \
	crypt.c file.c isearch.c search.c termio.c tags.c tcap.c

.include <bsd.prog.mk>
