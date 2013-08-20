#define  INCL_BASE
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static BOOL fOnCAD = TRUE;

void NcdAnalArgs (int argc, char *argv[]);
void NcdHelpArgs (void);
BOOL NcdSwitchCAD (BOOL fSwitch);


main(int argc, char *argv[], char *envp[])
{
   printf ("NoCAD 1.0 Copyright (c) B. Kunrath 1993\n");

   NcdAnalArgs (argc, argv);
   NcdSwitchCAD (fOnCAD);

   return NO_ERROR;
}

void NcdAnalArgs (int argc, char *argv[])
{
    if (argc != 2)
    {
        NcdHelpArgs ();
        exit (-1);
    } 
    else 
    {
        if (strcmp (argv[1], "ON"))
        {
           fOnCAD = TRUE;
        }
        else
        {
           if (strcmp (argv[1], "OFF"))
           {
              fOnCAD = FALSE;
           }
           else
           {
               NcdHelpArgs ();
               exit (-1);
           } 
        } /* endif */
    }
    return;
}

void NcdHelpArgs (void)
{
    printf("NoCAD needs a parameter !\n");
    printf("Usage: NoCAD ON|OFF\n");
    printf("              ³  ÀÄÄÄ means no boot on CAD \n");
    printf("              ÀÄÄÄÄÄÄ means boot on CAD !\n");
    return;
}

BOOL NcdSwitchCAD (BOOL fSwitch)
{
    ULONG ulApiRet;
    HFILE hFile;
    ULONG ulAct;
    struct
    {
        USHORT usShiftState;
        BYTE   ucHotKeyMake;
        BYTE   ucHotKeyBreak;
        USHORT usHotKeyID;
    } chParms;
    ULONG ulParm;
    ULONG ulData;

    ulApiRet = DosOpen("KBD$",&hFile,&ulAct,0L,0L,1L,0x40,0L);
    if (ulApiRet)
    {
       return FALSE;
    }
    else 
    {
       if (fSwitch)
       {
          chParms.usHotKeyID = 1;
       } 
       else 
       {
          chParms.usHotKeyID = -1;
       } /* endif */
       ulParm = sizeof(chParms);
       ulData = 0;
       ulApiRet = DosDevIOCtl(hFile, 04, 0x56, &chParms, sizeof (chParms), &ulParm, NULL, 0L, &ulData);
       DosClose (hFile);
       if (ulApiRet)
          return FALSE;
    } /* endif */

}
