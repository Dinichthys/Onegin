#include <stdio.h>
#include <stdlib.h>

#include "my_io.h"
#include "my_assert.h"
#include "logging.h"
#include "helpful.h"
#include "line_info.h"

static size_t get_len_file (FILE* const stream);
static size_t parse_lines (struct line_info* const string, const size_t num_elem);

static const size_t multiplier = 2;
static const size_t shift = 1;

enum RESULT_OF_FUNC read_file (FILE* const stream, struct line_info* const string)
{
    ASSERT(stream != NULL, "Invalid argument for read_file\n");
    ASSERT(string != NULL, "Invalid argument for read_file\n");

    LOG(INFO, "to function read_file:\n"
              " stream = %p\n"
              " .line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
              " .real_number_lines = %lu\n .predicted_number_lines = %lu\n",
              stream, string->line, string->start_of_lines, string->end_of_lines,
              string->real_number_lines, string->predicted_number_lines);

    size_t num_elem = get_len_file (stream);
    string->line = (char*) calloc (num_elem + 2, sizeof (char));
    if (string->line == NULL)
    {
        return FAULT;
    }
    *(string->line) = '\0';

    fread ((void*) (string->line + 1), sizeof (char), num_elem, stream);

    string->predicted_number_lines = parse_lines (string, num_elem + 1);

    if (string->predicted_number_lines == 0)
    {
        return FAULT;
    }

    *(string->line + num_elem + 1) = '\0';
    return DONE;
}

static size_t get_len_file (FILE* const stream)
{
    ASSERT(stream != NULL, "Invalid argument for get_len_file\n");

    fseek (stream, 0L, SEEK_END);
    size_t return_val = (size_t) ftell (stream);
    fseek (stream, 0L, SEEK_SET);

    return return_val;
}

static size_t parse_lines (struct line_info* const string, const size_t num_elem)
{
    ASSERT(string->line != NULL, "Invalid argument for function parse_lines\n");

    string->start_of_lines [0] = string->line + shift;
    string->real_number_lines = 0;
    for (size_t i = 0; i < num_elem; i++)
    {
        if (string->line [i + shift] != '\n')
        {
            continue;
        }
        string->real_number_lines++;
        if (string->real_number_lines == string->predicted_number_lines)
        {
            string->predicted_number_lines *= multiplier;

            string->start_of_lines = (char**) realloc ((void*) string->start_of_lines,
                                                        (string->predicted_number_lines) * sizeof (char*));
            if (string->start_of_lines == NULL)
            {
                return 0;
            }

            string->end_of_lines   = (char**) realloc ((void*) string->end_of_lines,
                                                        (string->predicted_number_lines) * sizeof (char*));
            if (string->end_of_lines == NULL)
            {
                return 0;
            }
        }
        (string->start_of_lines) [string->real_number_lines]   = string->line + i + 1 + shift;
        (string->end_of_lines) [string->real_number_lines - 1] = string->line + i - 1 + shift;
        (string->line) [i + shift] = '\0';
    }

    (string->end_of_lines) [string->real_number_lines] = string->line + num_elem;

    return string->real_number_lines;
}

void my_fwrite (FILE* const stream, char* arr [], const size_t count, const bool reverse)
{
    ASSERT(stream != NULL, "Invalid argument for my_fwrite\n");
    ASSERT(arr    != NULL, "Invalid argument for my_fwrite\n");

    LOG(INFO, "Parameters for function my_fwrite:\n"
              " arr = %p\n count = %lu\n reverse = %lu\n",
              arr, count, reverse);

    for (size_t i = 0; i < count; i++)
    {
        if (reverse)
        {
            while (*(arr [i]) != '\0')
            {
                arr [i]--;
            }
            arr [i]++;
        }
        fputs (arr [i], stream);
        fputc ('\n', stream);
    }
}

enum RESULT_OF_FUNC my_fwrite_all_sort (FILE* const stream, char* arr_start [], char* arr_end [], const size_t count)
{
    ASSERT(stream    != NULL, "Invalid argument for my_fwrite_all_sort\n");
    ASSERT(arr_start != NULL, "Invalid argument for my_fwrite_all_sort\n");
    ASSERT(arr_end   != NULL, "Invalid argument for my_fwrite_all_sort\n");

    LOG(INFO, "struct string before function my_fwrite_all_sort:\n"
              " stream = %p\n arr_start = %p\n arr_end = %p\n count = %lu\n",
              stream, arr_start, arr_end, count);

    bool* printed = (bool*) calloc (count, sizeof (bool*));
    if (printed == NULL)
    {
        FREE_AND_NULL(printed);
        return FAULT;
    }
    for (size_t i = 0; i < count; i++)
    {
        printed [i] = false;
    }

    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            if (arr_end [j] == arr_start [i])
            {
                if (printed [j])
                {
                    break;
                }

                printed [j] = true;
                size_t index = j + 1;
                if (j == count - 1)
                {
                    index = j - 1;
                }

                while (printed [index])
                {
                    index++;

                    if (index == count)
                    {
                        fputs (arr_start [i], stream);
                        fputc ('\n', stream);
                        break;
                    }
                }

                if (index == count)
                {
                    break;
                }

                while (*(arr_end [index]) != '\0')
                {
                    arr_end [index]--;
                }
                arr_end [index]++;

                fputs (arr_start [i], stream);
                fputc ('\n', stream);


                fputs (arr_end [index], stream);
                fputc ('\n', stream);
                printed [index] = true;

                break;
            }
        }
    }

    FREE_AND_NULL(printed);
    return DONE;
}

void make_gap (FILE* const stream)
{
    ASSERT(stream != NULL, "Invalid argument for make_gap\n");

    for (int i = 0; i < 5; i++)
    {
        putc('\n', stream);
    }
}
