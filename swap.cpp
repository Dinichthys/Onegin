#include <string.h>
#include <stdint.h>

#include "logging.h"
#include "my_assert.h"
#include "swap.h"

static void  memcpy_for_swap (void* const ptr1, void* const ptr2, void* const change, size_t size);

void swap (void* const a, void* const b, const size_t size)
{
    ASSERT(a != NULL, "Invalid argument for function swap\n");
    ASSERT(b != NULL, "Invalid argument for function swap\n");

    LOG(DEBUG, " Parameters for function swap:\n"
                       " a = %p \n b = %p\n size = %lu\n",
                       a, b, size);

    char* ptr_1 = (char*) a;
    char* ptr_2 = (char*) b;

    for (size_t i = 0; i < size; i++)
    {
        char change =  ptr_1 [i];
                       ptr_1 [i] = ptr_2 [i];
                                   ptr_2 [i] = change;
    }
}

void vec_swap (void* a, void* b, size_t size)
{
    ASSERT(a != NULL, "Invalid argument for function vec_swap\n");
    ASSERT(b != NULL, "Invalid argument for function vec_swap\n");

    while (size > sizeof (uint64_t))
    {
        uint64_t change = 0;

        memcpy_for_swap (a, b, &change, sizeof (uint64_t));

        a = (uint8_t*) a + sizeof (uint64_t);
        b = (uint8_t*) b + sizeof (uint64_t);
        size -= sizeof (uint64_t);
    }

    if (size > sizeof (uint32_t))
    {
        uint32_t change = 0;

        memcpy_for_swap (a, b, &change, sizeof (uint32_t));

        a = (uint8_t*) a + sizeof (uint32_t);
        b = (uint8_t*) b + sizeof (uint32_t);
        size -= sizeof (uint32_t);
    }

    if (size > sizeof (uint16_t))
    {
        uint16_t change = 0;

        memcpy_for_swap (a, b, &change, sizeof (uint16_t));

        a = (uint8_t*) a + sizeof (uint16_t);
        b = (uint8_t*) b + sizeof (uint16_t);
        size -= sizeof (uint16_t);
    }

    if (size > sizeof (uint8_t))
    {
        uint8_t change = 0;

        memcpy_for_swap (a, b, &change, sizeof (uint8_t));

        a = (uint8_t*) a + sizeof (uint8_t);
        b = (uint8_t*) b + sizeof (uint8_t);
        size -= sizeof (uint8_t);
    }
}

static void memcpy_for_swap (void* const ptr1, void* const ptr2, void* const change, const size_t size)
{
    ASSERT(ptr1   != NULL, "Invalid argument for function memcpy_for_swap\n");
    ASSERT(ptr2   != NULL, "Invalid argument for function memcpy_for_swap\n");
    ASSERT(change != NULL, "Invalid argument for function memcpy_for_swap\n");

    memcpy (change, ptr1, size);
            memcpy (ptr1, ptr2, size);
                  memcpy (ptr2, change, size);
}
