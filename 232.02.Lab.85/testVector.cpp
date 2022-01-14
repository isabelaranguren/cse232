/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test vector.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   // Remove this to skip the unit tests
#endif // DEBUG

#include "testVector.h"     // for the vector unit tests
#include "vector.h"



/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestVector().run();
#endif // DEBUG
   
   return 0;
}

