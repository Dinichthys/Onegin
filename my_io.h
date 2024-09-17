#ifndef MY_IO_H
#define MY_IO_H

#include <stdio.h>

#include "my_assert.h"
#include "line_info.h"
#include "helpful.h"

enum RESULT_OF_FUNC read_file          (FILE* const stream, struct line_info* const string);
void my_fwrite                         (FILE* const stream,
                                        char* arr[], const size_t count, const bool reverse);
enum RESULT_OF_FUNC my_fwrite_all_sort (FILE* const stream,
                                        char* arr_start[], char* arr_end[], const size_t count);
void make_gap                          (FILE* const file);

#endif // MY_IO_H
