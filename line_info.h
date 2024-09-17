#ifndef LINE_INFO_H
#define LINE_INFO_H

struct line_info
{
    char*  line;
    char** start_of_lines;
    char** end_of_lines;
    size_t real_number_lines;
    size_t predicted_number_lines;
};

#endif // LINE_INFO_H
