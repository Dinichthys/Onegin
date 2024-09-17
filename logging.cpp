#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "logging.h"
#include "my_assert.h"

static enum LEVEL_LOG logging_lvl = DEBUG;
static const int year_shift       = 1900;

static void level_to_str (FILE* const stream,  const enum LEVEL_LOG level);

static void level_to_str (FILE* const stream, const enum LEVEL_LOG level)
{
    switch (level)
    {
        case DEBUG:
        {
            fprintf (stream, "[%s] \n", "DEBUG");
            break;
        }
        case INFO:
        {
            fprintf (stream, "[%s] \n", "INFO");
            break;
        }
        case WARNING:
        {
            fprintf (stream, "[%s] \n", "WARNING");
            break;
        }
        case ERROR:
        {
            fprintf (stream, "[%s] \n", "ERROR");
            break;
        }
        default:
        {
            assert (0 && "Program got wrong level of logging in function log");
            break;
        }
    }
}


void Log (const struct logging settings, const enum LEVEL_LOG level, const char * const format, ...)
{
    ASSERT(format != NULL, "Invalid argument for Log %p\n", format);

    if (level < logging_lvl)
    {
        return;
    }

    level_to_str (settings.set, level);
    fprintf (settings.set, "%s:%d (%s) %d sec %d min %d hours %d days %d month %d years\n",
             settings.file, settings.line, settings.func,
             settings.now->tm_sec, settings.now->tm_min,
             settings.now->tm_hour, settings.now->tm_mday,
             settings.now->tm_mon, settings.now->tm_year + year_shift);

    va_list param;
    va_start (param, format);
    vfprintf (settings.set, format, param);
    va_end (param);

    fprintf (settings.set, "\n");
}

void set_log_lvl (const enum LEVEL_LOG level)
{
    logging_lvl = level;
}
