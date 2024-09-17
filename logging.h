#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <time.h>

#define LOG(stream, level, format, ...)                                                                  \
    do                                                                                           \
    {                                                                                            \
        time_t seconds = time (NULL);                                                            \
        Log ({(stream), __FILE__, __func__, __LINE__, localtime(&seconds)}, level, format, __VA_ARGS__); \
    } while (0)

enum LEVEL_LOG
{
    DEBUG   = 1,
    INFO    = 2,
    WARNING = 3,
    ERROR   = 4,
};

struct logging
{
    FILE* set;

    const char* const file;

    const char* const func;

    int line;

    struct tm *now;
};

void set_log_lvl (const enum LEVEL_LOG level);
void Log (const struct logging parameter, const enum LEVEL_LOG level, const char * const format, ...);

#endif // LOGGING_H
