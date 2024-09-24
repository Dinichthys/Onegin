#include <stdlib.h>

#include "qsort.h"
#include "swap.h"
#include "my_assert.h"
#include "logging.h"
#include "helpful.h"

static void* partition (void *const base, const size_t nmemb, const size_t size,
                        int(*compar)(const void *, const void *));

void my_qsort (void *const base, const size_t nmemb, const size_t size,
              int(*compar)(const void *, const void *))
{
    ASSERT(base   != NULL, "Invalid argument for function qsort\n");
    ASSERT(compar != NULL, "Invalid argument for function qsort\n");

    if (nmemb < 2)
    {
        return;
    }
    void* mid = partition (base, nmemb, size, compar);

    if ((char*) mid > (char*) base)
    {
        my_qsort (base, ((char*) mid - (char*) base) / size, size, compar);
    }

    if ((char*) mid < (char*) base + (nmemb - 1) * size)
    {
        my_qsort ((char*) mid + size, ((char*) base + (nmemb - 1) * size - (char*) mid) / size, size, compar);
    }
}

static void* partition (void *const base, const size_t nmemb, const size_t size,
                        int(*compar)(const void *, const void *))
{
    ASSERT(base   != NULL, "Invalid argument for function partition\n");
    ASSERT(compar != NULL, "Invalid argument for function partition\n");

    LOG(DEBUG, " Parameters for function partition:\n"
               " base = %p \n nmemb = %lu\n size = %lu\n",
               base, nmemb, size);

    char* left   = (char*) base;
    char* right  = (char*) base + ((nmemb - 1) * size);
    char* mid    = (char*) base + ( nmemb / 2  * size);

    size_t count = 1;
    while (left < right)
    {
        LOG(DEBUG, " left = %p \n right = %p\n mid = %p\n"
                   " Iteration № %lu\n",
                   left, right, mid, count);
        count++;

        while ((left < right) && (compar (left, mid) <= 0) && (left < mid))
        {
            left += size;
        }

        LOG(DEBUG, " left = %p \n right = %p\n", left, right);

        while ((left < right) && (compar (right, mid) >= 0) && (right > mid))
        {
            right -= size;
        }

        LOG(DEBUG, " left = %p \n right = %p\n size = %lu\n", left, right, size);

        if (left < right)
        {
            vec_swap (left, right, size);

            if (left == mid)
            {
                mid = right;
            }
            else if (right == mid)
            {
                mid = left;
            }
        }

        LOG(DEBUG, " left = %p \n right = %p\n", left, right);
    }

    LOG(DEBUG, " left = %p \n right = %p\n", left, right);

    return mid;
}
