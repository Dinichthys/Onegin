#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_io.h"
#include "my_assert.h"
#include "sort.h"
#include "logging.h"
#include "line_info.h"

static const char*  onegin                 = "Eugene_Onegin.txt";
static const char*  sorted_onegin_straight = "Eugene_Onegin_straight.txt";
static const char*  sorted_onegin_reversed = "Eugene_Onegin_reversed.txt";
static const char*  sorted_onegin          = "Eugene_Onegin_sorted.txt";
static const size_t predicted_number       = 200;

// var_iables
// FuncTions
// LineInfo
// kOnegin

int main () // TODO get filename from agrc argv
{
    set_log_lvl (DEBUG);

    struct line_info string = {.line = NULL, .start_of_lines = NULL, .end_of_lines = NULL,
                               .real_number_lines = 0, .predicted_number_lines = predicted_number};

    FILE* input = fopen (onegin, "rb");
    if (input == NULL)
    {
        fprintf (stderr, "Can't open file %s for reading\n", onegin);
        return EXIT_FAILURE;
    }

    FILE* output_straight = fopen (sorted_onegin_straight, "w");
    if (output_straight == NULL)
    {
        fprintf (stderr, "Can't open file %s for writing\n", sorted_onegin_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    FILE* output_reversed = fopen (sorted_onegin_reversed, "w");
    if (output_reversed == NULL)
    {
        fprintf (stderr, "Can't open file %s for writing\n", sorted_onegin_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    FILE* output_all = fopen (sorted_onegin, "w");
    if (output_all == NULL)
    {
        fprintf (stderr, "Can't open file %s for writing\n", sorted_onegin);
        CLOSE_AND_NULL(output_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    string.start_of_lines = (char**) calloc (string.predicted_number_lines, sizeof(char*));
    if (string.start_of_lines == NULL)
    {
        fprintf (stderr, "%s", "Can't calloc memory for arr_ptr_start\n");
        CLOSE_AND_NULL(output_all);
        CLOSE_AND_NULL(output_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    string.end_of_lines   = (char**) calloc (string.predicted_number_lines, sizeof(char*));
    if (string.end_of_lines == NULL)
    {
        fprintf (stderr, "%s", "Can't calloc memory for arr_ptr_start\n");
        FREE_AND_NULL(string.start_of_lines);
        CLOSE_AND_NULL(output_all);
        CLOSE_AND_NULL(output_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    string.real_number_lines = 0;

    LOG(stderr, INFO, "to function result:\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    enum RESULT_OF_FUNC result = read_file (input, &string);
    if (result == FAULT)
    {
        fprintf (stderr, "%s", "The program can't complete function my_fread\n");
        FREE_AND_NULL(string.end_of_lines);
        FREE_AND_NULL(string.start_of_lines);
        CLOSE_AND_NULL(output_all);
        CLOSE_AND_NULL(output_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }


    LOG(stderr, INFO, "struct string before function sort (left to right):\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    sort (string.start_of_lines, string.real_number_lines, false);

    LOG(stderr, INFO, "struct string before function sort (left to right):\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    sort (string.end_of_lines, string.real_number_lines, true );

    LOG(stderr, INFO, "struct string before function my_fwrite (right to left):\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    my_fwrite (output_straight, string.start_of_lines, string.real_number_lines, false);

    LOG(stderr, INFO, "struct string before function my_fwrite (left to right):\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    my_fwrite (output_reversed, string.end_of_lines, string.real_number_lines, true);

    LOG(stderr, INFO, "struct string before function my_fwrite_all_sort:\n"
                      ".line = %p\n .start_of_lines = %p\n .end_of_lines = %p\n"
                      ".real_number_lines = %lu\n .predicted_number_lines = %lu\n",
                      string.line, string.start_of_lines, string.end_of_lines,
                      string.real_number_lines, string.predicted_number_lines);
    result = my_fwrite_all_sort (output_all,
                                 string.start_of_lines, string.end_of_lines, string.real_number_lines);

    FREE_AND_NULL(string.end_of_lines);
    FREE_AND_NULL(string.start_of_lines);
    CLOSE_AND_NULL(output_all);
    CLOSE_AND_NULL(output_reversed);
    CLOSE_AND_NULL(output_straight);
    CLOSE_AND_NULL(input);

    if (result == FAULT)
    {
        return EXIT_FAILURE;
    }
}
