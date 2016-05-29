#include <stdio.h>

#ifndef DEBUG_ENABLED
#define DEBUG_ENABLED 0
#endif

#ifndef DEBUG_OUT
#define DEBUG_OUT printf
#endif

#if DEBUG_ENABLED == 1
#define DEBUG( format, expr ) DEBUG_OUT( "'%s' => '"format"'\n", #expr, ( expr ) )
#else
#define DEBUG( format, expr )
#endif
