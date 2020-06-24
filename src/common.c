#include "common.h"

/**
 * @author Eduardo Oliveira; Carlos Daniel;
 * @email eduardo.oliveira@ieee.org; carlosdanielmiranda99@gmail.com;
 * @create date 06-05-2020 19:59:00
 * @modify date 06-05-2020 19:59:00
 * @desc Common code
 * @version 0.0.1
 */

/*!
* Procedure: Clean the buffer from the keyboard - Alternative to fflush(stdin)
*/
void cleanStdin()
{
    int c;
    // Clean the buffer until '\n' or End-of-file
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/*!
* Procedure: Clean the console - Works on both Windows/Linux
*/
void cls(void)
{
    system(CLEAR); return;
}