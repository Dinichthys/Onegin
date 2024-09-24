#include <ctype.h>

#include "compare.h"
#include "logging.h"
#include "my_assert.h"

static void skip_non_abc (const char** const s, const int step);

static void skip_non_abc (const char** const s, const int step)
{
    ASSERT(s != NULL, "Invalid argument for function skip_non_sym\n");

    while (!(isalpha (**s)) && (**s != '\0'))
    {
        *s += step;
    }
}

int compare (const void* const a, const void* const b)
{
    ASSERT(a != NULL, "Invalid argument for function my_strcmp\n");
    ASSERT(b != NULL, "Invalid argument for function my_strcmp\n");

    const char* s1 = *((const char**) a);
    const char* s2 = *((const char**) b);

    LOG(DEBUG, " s1 = %p \n s2 = %p\n", s1, s2);

    skip_non_abc (&s1, 1);
    skip_non_abc (&s2, 1);

    LOG(DEBUG, s1);
    LOG(DEBUG, s2);

    while ((tolower(*s1) == tolower(*s2)) && (*s1 != '\0'))
    {
        s1++;
        s2++;

        skip_non_abc (&s1, 1);
        skip_non_abc (&s2, 1);
    }

    return tolower(*s1) - tolower(*s2);
}

int compare_r (const void* const a, const void* const b)
{
    ASSERT(a != NULL, "Invalid argument for function my_strcmp\n");
    ASSERT(b != NULL, "Invalid argument for function my_strcmp\n");

    const char* s1 = *((const char**) a);
    const char* s2 = *((const char**) b);

    LOG(DEBUG, " s1 = %p \n s2 = %p\n", s1, s2);

    skip_non_abc (&s1, -1);
    skip_non_abc (&s2, -1);

    while ((tolower(*s1) == tolower(*s2)) && (*s1 != '\0'))
    {
        s1--;
        s2--;

        skip_non_abc (&s1, -1);
        skip_non_abc (&s2, -1);
    }

    return tolower(*s1) - tolower(*s2);
}
