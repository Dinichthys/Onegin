#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#include "print_error.h"
#include "logging.h"

#define ASSERT(a, ...)                                  \
    do                                                  \
    {                                                   \
        if ((a) == 0)                                   \
        {                                               \
            print_err (stderr, __VA_ARGS__);            \
            abort();                                    \
        };                                              \
    }                                                   \
    while (0)

#endif // MY_ASSERT_H
