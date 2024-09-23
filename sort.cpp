#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>

#include "sort.h"
#include "my_assert.h"
#include "logging.h"

void sort (void* arr, const size_t count, const size_t size, int (*comp) (const void*, const void*))
{
    ASSERT(arr != NULL, "Invalid argument for function sort\n");

    LOG(INFO, "struct string before function sort:\n"
              " arr = %p\n count = %lu\n size = %lu\n",
              arr, count, size);

    for (size_t i = 0; i < count - 1; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            if (comp ((char*) arr + i * size, (char*) arr + j * size) > 0)
            {
                for (size_t k = 0; k < size; k++)
                {
                    char change = *((char*) arr + i * size + k);
                                  *((char*) arr + i * size + k) = *((char*) arr + j * size + k);
                                                                  *((char*) arr + j * size + k) = change;
                }
            }
        }
    }
}
