#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include "board.h"

void io_read_line(char *buf, int n);
bool io_parse_coord(const char *s, int *r, int *c, Board *b);
char io_read_choice(const char *prompt, const char *opts);
void clear_stdin(void);

#endif
