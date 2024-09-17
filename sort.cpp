#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>

#include "sort.h"
#include "my_assert.h"

static int my_strcmp (char* s1, char* s2, const bool reverse);

static int my_strcmp (char* s1, char* s2, const bool reverse)
{
    ASSERT(s1 != NULL, "Invalid argument for function my_strcmp\n");
    ASSERT(s2 != NULL, "Invalid argument for function my_strcmp\n");

    int step = reverse ? -1 : 1;

    while (!(isalpha (*s1)))
    {
        s1 += step;
    }
    while (!(isalpha (*s2)))
    {
        s2 += step;
    }

    while ((tolower(*s1) == tolower(*s2)) && (*s1 != '\0'))
    {
        s1 += step;
        s2 += step;
    }

    return tolower(*s1) - tolower(*s2);
}

void sort (char** arr, const size_t count, const bool reverse)
{
    ASSERT(arr != NULL, "Invalid argument for function sort\n");

    for (size_t i = 0; i < count - 1; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            if (my_strcmp (arr [i], arr [j], reverse) > 0)
            {
                char* change = arr [i];
                               arr [i] = arr [j];
                                         arr [j] = change;
            }
        }
    }
}
