#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_io.h"
#include "my_assert.h"
#include "sort.h"
#include "logging.h"
#include "line_info.h"
#include "qsort.h"
#include "parse_argv.h"

static const char*  onegin                 = "Eugene_Onegin.txt";
static const char*  sorted_onegin_straight = "Eugene_Onegin_straight.txt";
static const char*  sorted_onegin_reversed = "Eugene_Onegin_reversed.txt";
static const char*  sorted_onegin          = "Eugene_Onegin_sorted.txt";
static const size_t predicted_number       = 200;

int main (const int argc, const char* const argv[])
{
    set_log_lvl (INFO);

    settings_of_program_t set = {.stream_in = NULL, .stream_out = NULL, .stream_err = NULL,
                                 .stop_program = false};
    parse_argv (argc, argv, &set);
    if (set.stop_program)
    {
        fprintf (stderr, "User wrote odd symbols in the terminal.\n");
        return EXIT_FAILURE;
    }

    set_log_file (set.stream_err);

    struct line_info string = {.line = NULL, .start_of_lines = NULL, .end_of_lines = NULL,
                               .real_number_lines = 0, .predicted_number_lines = predicted_number};

    FILE* input = NULL;
    if (set.stream_in == NULL)
    {
        input = fopen (onegin, "rb");
        if (input == NULL)
        {
            fprintf (stderr, "Can't open file %s for reading\n", onegin);
            return EXIT_FAILURE;
        }
    }
    else
    {
        input = set.stream_in;
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

    FILE* output_all = NULL;
    if (set.stream_out == NULL)
    {
        output_all = fopen (sorted_onegin, "w");
        if (output_all == NULL)
        {
            fprintf (stderr, "Can't open file %s for writing\n", sorted_onegin);
            CLOSE_AND_NULL(output_reversed);
            CLOSE_AND_NULL(output_straight);
            CLOSE_AND_NULL(input);
            return EXIT_FAILURE;
        }
    }
    else
    {
        output_all = set.stream_out;
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

    string.end_of_lines = (char**) calloc (string.predicted_number_lines, sizeof(char*));
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

    enum RESULT_OF_FUNC result = read_file (input, &string);
    if (result == FAULT)
    {
        fprintf (stderr, "The program can't complete function my_fread\n");
        FREE_AND_NULL(string.line);
        FREE_AND_NULL(string.end_of_lines);
        FREE_AND_NULL(string.start_of_lines);
        CLOSE_AND_NULL(output_all);
        CLOSE_AND_NULL(output_reversed);
        CLOSE_AND_NULL(output_straight);
        CLOSE_AND_NULL(input);
        return EXIT_FAILURE;
    }

    my_qsort (string.start_of_lines, string.real_number_lines, sizeof (char*), compare);

    sort (string.end_of_lines, string.real_number_lines, sizeof (char*), compare_r);

    my_fwrite (output_straight, string.start_of_lines, string.real_number_lines, false);

    my_fwrite (output_reversed, string.end_of_lines, string.real_number_lines, true);

    result = my_fwrite_all_sort (output_all,
                                 string.start_of_lines, string.end_of_lines, string.real_number_lines);

    FREE_AND_NULL(string.end_of_lines);
    FREE_AND_NULL(string.start_of_lines);
    FREE_AND_NULL(string.line);
    CLOSE_AND_NULL(output_all);
    CLOSE_AND_NULL(output_reversed);
    CLOSE_AND_NULL(output_straight);
    CLOSE_AND_NULL(input);

    return (result == FAULT)
                ? EXIT_FAILURE
                : EXIT_SUCCESS;
}
