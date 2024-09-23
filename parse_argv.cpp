#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <getopt.h>

#include "parse_argv.h"
#include "my_assert.h"
#include "logging.h"

static void print_help (void);

void parse_argv (const int argc, const char * const argv[], settings_of_program_t * const set)
{
    ASSERT(argv != NULL, "Invalid arguments for function parse_argv\n");
    ASSERT(set != NULL,  "Invalid arguments for function parse_argv\n");

    const struct option modifications [] =
    {
        {"help",    0, 0, 'h'},
        {0,         0, 0,  0 }
    };

    int mode = 0;
    int long_index = 0;
    int count_iterate = 0;

    while (mode != -1)
    {
        count_iterate++;
        mode = getopt_long (argc, (char* const*) argv, "+o:i:e:h", modifications, &long_index);
        switch (mode)
        {
            case 'o':
            {
                set->stream_out = fopen (optarg, "w");
                if (set->stream_out == NULL)
                {
                    mode = -1;
                    set->stop_program = true;
                    LOG(ERROR, "There is no files with name %s\n", optarg);
                }
                count_iterate++;
                break;
            }
            case 'i':
            {
                set->stream_in = fopen (optarg, "r");
                if (set->stream_in == NULL)
                {
                    mode = -1;
                    set->stop_program = true;
                    LOG(ERROR, "There is no files with name %s\n", optarg);
                }
                count_iterate++;
                break;
            }
            case 'e':
            {
                set->stream_err = fopen (optarg, "w");
                if (set->stream_err == NULL)
                {
                    mode = -1;
                    set->stop_program = true;
                    LOG(ERROR, "There is no files with name %s\n", optarg);
                }
                count_iterate++;
                break;
            }
            case 'h':
            {
                print_help ();
                mode = -1;
                set->stop_program = true;
                break;
            }
            case -1:
            {
                if (argc != count_iterate)
                {
                    mode = -1;
                    set->stop_program = true;
                    LOG(ERROR, "There are odd symbols in the terminal.\n");
                }
                break;
            }
            default:
            {
                printf("Invalid name of command in the terminal.\n");
                mode = -1;
                set->stop_program = true;
                LOG(ERROR, "Invalid name of command in the terminal.\n");
                ASSERT(0, "Invalid name of command in the terminal.\n");
                break;
            }
        }
    }
}

static void print_help (void)
{
    printf (" There is list of parameters of that program.\n"
                            " \"-i\"                :"
                            " you can change the stream of input"
                            " and write the name of place of input after it.\n"
                            " \"-o\"                :"
                            " you can change the stream of output"
                            " and write the name of place of output after it.\n"
                            " \"-e\"                :"
                            " you can change the stream of output for errors"
                            " and write the name of place of output after it.\n"
                            " \"--verbose\" or \"-v\" :"
                            " makes the analytic investigation verbose.\n");
}
