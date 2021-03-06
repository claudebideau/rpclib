/*!
 * \file trace.cpp
 * \author Claude BIDEAU
 * \version 0.1
 * \brief This module provides print traces definition with different level.
 * \date  2014/03/21
 * 
 * \section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This module provides  print traces definition with different level.
 *
 */

/**********************************************************************
**   1a. Standard Library Include                                    **
**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdarg.h>
#include <pthread.h>

/**********************************************************************
**   1b. Include files  (own)                                        **
**********************************************************************/
#include "trace.h"
#include <time.h>


/**********************************************************************
**   2a.   External Functions                                        **
**********************************************************************/

/**********************************************************************
**   2b.   External Data                                             **
**********************************************************************/

/**********************************************************************
**   3.  Type Definitions                                            **
**********************************************************************/


/**********************************************************************
**   4.  Global Functions (Exported)                                 **
**********************************************************************/

/**********************************************************************
**   5.  Local Functions                                             **
**********************************************************************/

/**********************************************************************
**   6.  Macros / Defines                                            **
**********************************************************************/

/**********************************************************************
**   7.  Global Data                                                 **
**********************************************************************/

unsigned int E_u32TraceLevel= (  TRACES_LEVEL_ERROR \
                         | TRACES_LEVEL_WARNING \
                         | TRACES_LEVEL_CMD \
                         | TRACES_LEVEL_INFO \
                         | TRACES_LEVEL_MSG \
                        );
                         // | TRACES_LEVEL_LOAD \
                         // | TRACES_LEVEL_DEBUG \
                        

/**********************************************************************
************************* Start of code      *************************/


/**
 * @brief print trace to console (stdout)
 * @author Claude Bideau
 * @date 2014/03/21
 * @param cat trace level
 * @param fmt string format
 * @param ... parameters
 * @return printf status
 * @details
 * @note
 * @todo
 *
 */
int print_trace(char * fmt,...)
{
    va_list args;
    static char new_fmt[4096];
    int res = 0;
    time_t timestamp;
#ifdef USE_SPINLOCK
    static pthread_spinlock_t  L_tsPrintSpinlock;
#else
    static pthread_mutex_t L_tsPrintMutex;
#endif

#ifdef USE_SPINLOCK
    pthread_spin_lock(&L_tsPrintSpinlock);
#else    
    pthread_mutex_lock (&L_tsPrintMutex);
#endif

    memset(new_fmt, 0, sizeof(new_fmt));

    /* Build the string to display */
    timestamp = time(NULL);
    strftime(new_fmt, sizeof(new_fmt), "%x %X -- ", localtime(&timestamp));
    strcat(new_fmt,fmt);
    //~ sprintf((char *)&str[len],MODULE_NAME": ");
    //~ len = strlen(str);
    va_start(args, fmt);
    res= vfprintf(stdout, new_fmt, args);
    va_end(args);

#ifdef USE_SPINLOCK
    pthread_spin_unlock(&L_tsPrintSpinlock);
#else    
    pthread_mutex_unlock (&L_tsPrintMutex);
#endif

    fflush(stdout);

    return res;
}
/* EOP TRACE */



/**
 * @brief conversion string to byte array
 * @author Claude Bideau
 * @date 2014/03/21
 * @param F_pcStr input string
 * @param F_u8aData output hex array
 * @param F_pcaSeperator delimitor
 * @param F_caStrConv string 2 byte format default (%x)
 * @return length
 * @details
 * @note
 * @todo
 *
 */
int Q_i32Str2Byte(const char * F_pcStr, unsigned char * F_u8aData, char * F_pcaSeperator, char * F_caStrConv)
{
    unsigned int L_u32Idx;
    int    L_i32IdxCopy;
    int    L_i32IdxData;
    int    L_i32Value;
    char   L_caStrData[3];
    char   L_caStrConv[10];

    L_u32Idx=0;
    L_i32IdxCopy=0;
    L_i32IdxData=0;
    L_caStrData[0]='\0';
    L_caStrData[2]='\0';

    if (F_pcaSeperator == NULL )
    {
        while (L_u32Idx < strlen(F_pcStr))
        {
            /* no separator => allways hex convertion */
            L_caStrData[L_i32IdxCopy++] = F_pcStr[L_u32Idx];
            if ((L_u32Idx&0x01)==1)
            {
                sscanf(L_caStrData,"%x",(unsigned int *) &L_i32Value);
                F_u8aData[L_i32IdxData] = (unsigned char) L_i32Value;
                L_i32IdxData++;
                /* clear buffer */
                L_i32IdxCopy=0;
            }
            L_u32Idx++;
        }
    }
    else
    {
        if (F_caStrConv == NULL )
        {
            /* default case hexadecimale conversion */
            strcpy(L_caStrConv,"%x");
        }
        else
        {
            strcpy(L_caStrConv,F_caStrConv);
        }
        while (L_u32Idx < strlen(F_pcStr))
        {
            if (strchr(F_pcaSeperator,F_pcStr[L_u32Idx]) !=NULL)
            {
                L_caStrData[L_i32IdxCopy]= '\0';
                sscanf(L_caStrData,L_caStrConv,&L_i32Value);
                F_u8aData[L_i32IdxData] = (unsigned char) L_i32Value;

                L_i32IdxData++;
                L_i32IdxCopy=0;
            }
            else
            {
                L_caStrData[L_i32IdxCopy++] = F_pcStr[L_u32Idx];
            }
            L_u32Idx++;
        }
        if (L_i32IdxCopy != 0)
        {
            L_caStrData[L_i32IdxCopy]= '\0';
            sscanf(L_caStrData,L_caStrConv,&L_i32Value);
            F_u8aData[L_i32IdxData] = (unsigned char) L_i32Value;
            L_i32IdxData++;
        }

    }
    return L_i32IdxData;
}

/**
 * @brief conversion byte array to string
 * @author Claude Bideau
 * @date 2014/03/21
 * @param F_u8aData input hex array
 * @param F_pcStr output string
 * @param F_pcaSeperator delimitor
 * @param F_caStrConv string 2 byte format default (%x)
 * @param F_u32Size array size
 * @return length
 * @details
 * @note
 * @todo
 *
 */
int Q_i32Byte2Str(unsigned char * F_u8aData, char * F_pcStr, char * F_caStrConv, char * F_pcaSeperator, unsigned int F_u32Size)
{
    unsigned int L_u32Idx;
    int    L_i32IdxCopy;
    int    L_i32IdxData;
    char   L_caStrConv[10];
    char   L_caStrData[10];

    L_u32Idx=0;
    L_i32IdxCopy=0;
    L_i32IdxData=0;

    F_pcStr[0] = '\0';

    if (F_pcaSeperator == NULL )
    {
        while (L_u32Idx < F_u32Size)
        {
            /* no separator => allways hex convertion */
            sprintf(L_caStrData,"%02x",F_u8aData[L_u32Idx]);
            strcat(F_pcStr,L_caStrData);
            L_u32Idx++;
        }
    }
    else
    {
        if (F_caStrConv == NULL )
        {
            /* default case hexadecimale conversion */
            strcpy(L_caStrConv,"%02x");
        }
        else
        {
            strcpy(L_caStrConv,F_caStrConv);
        }

        while (L_u32Idx < F_u32Size)
        {
            sprintf(L_caStrData,L_caStrConv,F_u8aData[L_u32Idx]);
            strcat(F_pcStr,L_caStrData);
            if (L_u32Idx< (F_u32Size-1))
            {
                strcat(F_pcStr,F_pcaSeperator);
            }
            L_u32Idx++;
        }
    }
    return strlen(F_pcStr);
}

/**********************************************************************
*************************    END MODULE *******************************
**********************************************************************/
