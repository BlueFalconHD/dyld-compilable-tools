// _simple.h - Header File

#ifndef _SIMPLE_H
#define _SIMPLE_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque type for the simple string buffer
typedef struct SimpleString SimpleString;

// Allocate a new SimpleString
SimpleString* _simple_salloc(void);

// Free a SimpleString
void _simple_sfree(SimpleString* s);

// Return the C-string from SimpleString
const char* _simple_string(const SimpleString* s);

// Move the insertion point to the end of the existing string in the buffer
void _simple_sresize(SimpleString* s);

// Write formatted data to SimpleString (appending to existing content)
int _simple_vsprintf(SimpleString* s, const char* format, va_list args);

const char *_simple_getenv(const char *envp[], const char *var);

#ifdef __cplusplus
}
#endif

#endif // _SIMPLE_H

