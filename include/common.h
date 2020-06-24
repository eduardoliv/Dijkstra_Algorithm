#ifndef COMMON_H_ /*INCLUDE GUARD*/
#define COMMON_H_

#ifdef _WIN32
#define CLEAR "cls"
#else // CLS In any other OS
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <stdlib.h>

// Pre-defined data types
typedef enum
{
    false,
    true
} bool;

/*!
* Procedure: Clean the buffer from the keyboard - Alternative to fflush(stdin)
*/
void cleanStdin();

/*!
* Procedure: Clean the console - Works on both Windows/Linux
*/
void cls(void);

#endif /*COMMON_H_*/