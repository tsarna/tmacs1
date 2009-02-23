#include "estruct.h"

#if FSE

/* donodemenu.c,v 1.1.1.1 1993/10/22 18:55:09 tsarna Exp */

#include <ctype.h>
#include "bbxbase.h"
#include "bbxshell.h"
#include "bbxdefines.h"

void
DoNodeMenu()
{
        char buf[2];

        SetMaybeAskMore(0);
        oLine("Node Commands (List/Gag/Prev/#/Notify/?=Help): ");
        buf[0] = iChar();
        buf[1] = '\0';

        if (islower(buf[0]))
                buf[0] = toupper(buf[0]);

        oLine(buf);

        if ((buf[0] == 'L') || (buf[0] == 'P') || (buf[0] == '?')) {
                SetMaybeAskMore(0);
                CLS();
        } else {
                oLine("\n");
        }

        Menu_Command(61, buf);
        AskMore();
}


#endif
