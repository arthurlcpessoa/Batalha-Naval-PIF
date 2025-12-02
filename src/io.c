#include "io.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void io_read_line(char *buf, int n) {
    if (!fgets(buf, n, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
}

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool io_parse_coord(const char *s, int *r, int *c, Board *b) {
    if (!s || !b) return false;
    int i = 0;
    while (s[i] && isspace((unsigned char)s[i])) ++i;
    if (!s[i]) return false;
    char colc = s[i];
    if (!isalpha((unsigned char)colc)) return false;
    colc = toupper((unsigned char)colc);
    int col = colc - 'A';
    ++i;
    if (col < 0 || col >= b->cols) return false;
    int row = 0;
    if (!isdigit((unsigned char)s[i])) return false;
    while (s[i] && isdigit((unsigned char)s[i])) {
        row = row * 10 + (s[i] - '0');
        ++i;
    }
    if (row < 1 || row > b->rows) return false;
    *r = row - 1;
    *c = col;
    return true;
}

char io_read_choice(const char *prompt, const char *opts) {
    char buf[64];
    while (1) {
        printf("%s", prompt);
        io_read_line(buf, sizeof(buf));
        if (!buf[0]) continue;
        char ch = toupper((unsigned char)buf[0]);
        for (int i = 0; opts[i]; ++i) {
            if (toupper((unsigned char)opts[i]) == ch) return ch;
        }
        printf("Opção inválida.\n");
    }
}
