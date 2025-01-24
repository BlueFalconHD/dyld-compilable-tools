//
//  _simple.c.h
//  dyld
//
//  Created by Hayes Dombroski on 1/22/25.
//

#include "_simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Define the SimpleString structure
struct SimpleString {
    char* data;
    size_t size;       // Current length of the string
    size_t capacity;   // Total capacity of the allocated buffer
};

// Allocate a new SimpleString with an initial capacity
SimpleString* _simple_salloc(void) {
    size_t initial_capacity = 256;  // Initial capacity can be adjusted as needed
    SimpleString* s = (SimpleString*)malloc(sizeof(SimpleString));
    if (s == NULL) {
        return NULL;
    }
    s->data = (char*)malloc(initial_capacity);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    s->data[0] = '\0';
    s->size = 0;
    s->capacity = initial_capacity;
    return s;
}

// Free the SimpleString
void _simple_sfree(SimpleString* s) {
    if (s != NULL) {
        free(s->data);
        free(s);
    }
}

// Return the C-string from SimpleString
const char* _simple_string(const SimpleString* s) {
    return s->data;
}

// Move the insertion point to the end of the existing string in the buffer
void _simple_sresize(SimpleString* s) {
    s->size = strlen(s->data);
}

// Resize the buffer capacity to at least new_capacity
static int _simple_srealloc(SimpleString* s, size_t new_capacity) {
    if (new_capacity <= s->capacity) {
        return 0;  // No need to resize
    }
    char* new_data = (char*)realloc(s->data, new_capacity);
    if (new_data == NULL) {
        return -1;  // Memory allocation failed
    }
    s->data = new_data;
    s->capacity = new_capacity;
    return 0;
}

// Write formatted data to SimpleString, appending to existing content
int _simple_vsprintf(SimpleString* s, const char* format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);

    // Calculate the required space for the new formatted string
    int required = vsnprintf(NULL, 0, format, args_copy) + 1;  // +1 for null terminator
    if (required <= 0) {
        va_end(args_copy);
        return -1;
    }

    size_t total_required = s->size + (size_t)required;
    if (total_required > s->capacity) {
        // Need to increase capacity
        size_t new_capacity = s->capacity * 2;
        while (new_capacity < total_required) {
            new_capacity *= 2;
        }
        if (_simple_srealloc(s, new_capacity) != 0) {
            va_end(args_copy);
            return -1;
        }
    }

    // Append the formatted string to the existing data
    int written = vsnprintf(s->data + s->size, s->capacity - s->size, format, args);
    if (written >= 0) {
        s->size += (size_t)written;
    }

    va_end(args_copy);
    return written;
}

const char *_simple_getenv(const char *envp[], const char *var) {
    if (envp == NULL || var == NULL) {
        return NULL;
    }
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], var, strlen(var)) == 0) {
            return envp[i] + strlen(var) + 1;
        }
    }
    return NULL;
}
