#ifndef SETTINGS_OF_PROGRAM
#define SETTINGS_OF_PROGRAM

#include <stdio.h>

typedef struct settings_of_program
{
    FILE* stream_in;
    FILE* stream_out;
    FILE* stream_err;
    bool stop_program;
} settings_of_program_t;

void  parse_argv (const int argc, const char * const argv[], settings_of_program_t * const set);

#endif // SETTINGS_OF_PROGRAM
