/* Created by Joseph Phan
* Edit Start Up Banner for Minix. Found this main file by using Grep
* in terminal (located in /usr/src/kernel).
* NOTE: this file only contains part of the main.c for minix 
*/

/*===========================================================================*
*				announce				     *
*===========================================================================*/
PRIVATE void announce(void)
{
    /* Display the MINIX startup banner. */
    printf("\nMINIX %s.%s. "
    #ifdef _SVN_REVISION
    "(" _SVN_REVISION ")\n"
    #endif
    "Copyright 2010, Vrije Universiteit, Amsterdam, The Netherlands\n",
    OS_RELEASE, OS_VERSION);
    printf("MINIX is open source software, see http://www.minix3.org\n");
    printf("EXTRA PRINT STATEMENT\n"); //added this extra print statement
    /*To Test Code, Recompile minix
        "make world", then call
        "reboot" outside kernel directory
    */
}
