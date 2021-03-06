//////////////////////////////////////////////////////////////////////
// File - lpt_lib.h
//
// Library for accessing the LPT card,
// Code was generated by DriverWizard v6.21 - http://www.jungo.com.
// The library accesses the hardware via WinDriver functions.
// 
// Copyright (c) 2004 Jungo Ltd.  http://www.jungo.com
// 
//////////////////////////////////////////////////////////////////////

#ifndef _LPT_LIB_H_
#define _LPT_LIB_H_

#include "LPTinclude/windrvr.h"
#include "LPTinclude/windrvr_int_thread.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    LPT_MODE_BYTE   = 0,
    LPT_MODE_WORD   = 1,
    LPT_MODE_DWORD  = 2,
    LPT_MODE_QWORD  = 3
};
typedef DWORD LPT_MODE;

enum
{
    LPT_IO_Range1 = 0,
};
typedef DWORD LPT_ADDR;

// Number of IO and memory ranges
enum { LPT_ITEMS = 1 };

enum{ LPT_IntA = 1 };
enum{ LPT_TOTAL_ITEMS = 2 };

// IO ranges definitions
enum { LPT_IO_Range1_ADDR = 0x378 };
enum { LPT_IO_Range1_BYTES = 0x8 };

// Interrupts definitions
enum { LPT_IntA_IRQ = 0x7 };
enum { LPT_IntA_OPTIONS = 00 };

// LPT register definitions 
enum { LPT_data_SPACE = LPT_IO_Range1 };
enum { LPT_data_OFFSET = 0x0 };
enum { LPT_status_SPACE = LPT_IO_Range1 };
enum { LPT_status_OFFSET = 0x1 };
enum { LPT_control_SPACE = LPT_IO_Range1 };
enum { LPT_control_OFFSET = 0x2 };

typedef struct LPT_STRUCT *LPT_HANDLE;

typedef struct
{
    DWORD dwCounter;   // number of interrupts received
    DWORD dwLost;      // number of interrupts yet to be handled
    BOOL fStopped;     // was the interrupt disabled during wait
} LPT_IntA_RESULT;

typedef void (DLLCALLCONV *LPT_IntA_HANDLER)(LPT_HANDLE hLPT, LPT_IntA_RESULT *intResult);

// Function: LPT_Open()
//   Register an ISA card to enable working with it.
//   The handle returned from this function is used by most of the functions in this file.
BOOL LPT_Open (LPT_HANDLE *phLPT);

// Function: LPT_RegisterWinDriver()
//   Enter a license string into WinDriver module.
DWORD LPT_RegisterWinDriver(void);

// Function: LPT_Close()
//   Unregister an opened card.
void LPT_Close(LPT_HANDLE hLPT);

// General read/write functions

// Function: LPT_ReadWriteBlock()
//   Read/Write data from/to the card's memory/IO into/from a given buffer.
void LPT_ReadWriteBlock(LPT_HANDLE hLPT, LPT_ADDR addrSpace,
    DWORD dwOffset, BOOL fRead, PVOID buf, DWORD dwBytes, LPT_MODE mode);

// Function: LPT_ReadByte()
//   Read a Byte from the card's memory/IO.
BYTE LPT_ReadByte (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset);

// Function: LPT_ReadWord()
//   Read a Word from the card's memory/IO.
WORD LPT_ReadWord (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset);

// Function: LPT_ReadDword()
//   Read a Dword from the card's memory/IO.
UINT32 LPT_ReadDword (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset);

// Function: LPT_ReadQword()
//   Read a Qword from the card's memory/IO.
UINT64 LPT_ReadQword (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset);

// Function: LPT_WriteByte()
//   Write a Byte to the card's memory/IO.
void LPT_WriteByte (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset, BYTE data);

// Function: LPT_WriteWord()
//   Write a Word to the card's memory/IO.
void LPT_WriteWord (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset, WORD data);

// Function: LPT_WriteDword()
//   Write a Dword to the card's memory/IO.
void LPT_WriteDword (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset, UINT32 data);

// Function: LPT_WriteQword()
//   Write a Qword to the card's memory/IO.
void LPT_WriteQword (LPT_HANDLE hLPT, LPT_ADDR addrSpace, DWORD dwOffset, UINT64 data);

// Function: LPT_Readdata()
//   Read from data register.
BYTE LPT_Readdata (LPT_HANDLE hLPT);

// Function: LPT_Writedata()
//   Write to data register.
void LPT_Writedata (LPT_HANDLE hLPT, BYTE data);

// Function: LPT_Readstatus()
//   Read from status register.
BYTE LPT_Readstatus (LPT_HANDLE hLPT);

// Function: LPT_Writestatus()
//   Write to status register.
void LPT_Writestatus (LPT_HANDLE hLPT, BYTE data);

// Function: LPT_Readcontrol()
//   Read from control register.
BYTE LPT_Readcontrol (LPT_HANDLE hLPT);

// Function: LPT_Writecontrol()
//   Write to control register.
void LPT_Writecontrol (LPT_HANDLE hLPT, BYTE data);


// Interrupts handling functions

// Function: LPT_IntAIsEnabled()
//   Check if the interrupt is enabled.
BOOL LPT_IntAIsEnabled (LPT_HANDLE hLPT);

// Function: LPT_IntAEnable()
//   Enable the interrupt.
BOOL LPT_IntAEnable (LPT_HANDLE hLPT, LPT_IntA_HANDLER funcIntHandler);

// Function: LPT_IntADisable()
//   Disable the interrupt.
void LPT_IntADisable (LPT_HANDLE hLPT);

// If an error occurs, this string will be set to contain a relevant error message
extern CHAR LPT_ErrorString[];

#ifdef __cplusplus
}
#endif

#endif
