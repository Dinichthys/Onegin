#ifndef HELPFUL_H
#define HELPFUL_H

enum RESULT_OF_FUNC
{
    FAULT = 0,
    DONE  = 1,
};

#define CLOSE_AND_NULL(file)                            \
    do                                                  \
    {                                                   \
        if ((file) != NULL)                             \
        {                                               \
            fclose (file);                              \
            file = NULL;                                \
        }                                               \
    }                                                   \
    while (0)

#define FREE_AND_NULL(dynamic_ptr)                      \
    do                                                  \
    {                                                   \
        if ((dynamic_ptr) != NULL)                      \
        {                                               \
            free (dynamic_ptr);                         \
            dynamic_ptr = NULL;                         \
        }                                               \
    }                                                   \
    while (0)

#endif // HELPFUL_H
