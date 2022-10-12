#include <stdio.h>

#define USAGE "Usage: wbytes target [source]\n"
#define BUFSIZE 1024

const unsigned char nibbles[22][2] = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15},
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
};

int iswhtspace(unsigned char c);
unsigned char getval(unsigned char c);
void close_file(FILE *f, const char *filename, int del);

int main(int argc, char *argv[]) {
    FILE *fin;
    if (argc == 3) {
        // Open input file
        if((fin = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "Error opening file %s.\n", argv[2]);
            return 1;
        }
    }
    else if (argc == 2)
        fin = stdin;
    else {
        printf(USAGE);
        return 1;
    }

    // Open output file
    FILE *fout;
    if((fout = fopen(argv[1], "wb")) == NULL) {
        fprintf(stderr, "Error opening file %s.\n", argv[1]);
        return 1;
    }

    unsigned int ttlcharcnt = 0, ttlbytecnt = 0, bytecnt;
    unsigned char tknstart = 0, lastchar, curchar, bufin[BUFSIZE], bufout[BUFSIZE];

    while (fgets(bufin, BUFSIZE, fin) != NULL) {
        bytecnt = 0;
        for (char *p = bufin; *p; p++) {
            ttlcharcnt++;
            if (iswhtspace(*p))
                if (tknstart) {
                    fprintf(stderr, "Unexpected character found at position %u. [ascii %d]\n", ttlcharcnt, *p);
                    close_file(fout, argv[1], 1);
                    return 1;
                }
                else
                    continue;
            if ((curchar = getval(*p)) == 16) {
                fprintf(stderr, "Invalid character found at position %u. [ascii %d]\n", ttlcharcnt, *p);
                close_file(fout, argv[1], 1);
                return 1;
            }
            else {
                if (tknstart) {
                    bufout[bytecnt++] = lastchar << 4 | curchar;
                    tknstart = 0;
                }
                else {
                    lastchar = curchar;
                    tknstart = 1;
                }
            }
        }
        for (int i = 0; i < bytecnt; i++)
            if (fputc(bufout[i], fout) == EOF) {
                fprintf(stderr, "Failed to write to target file '%s'.\n", argv[1]);
                close_file(fout, argv[1], 1);
                return 1;
            }
        ttlbytecnt += bytecnt;
    }
    close_file(fout, argv[1], 0);
    printf("%u bytes written to target file '%s'.\nComplete.\n", ttlbytecnt, argv[1]);

    return 0;
}

int iswhtspace(unsigned char c) {
    int r = 0;
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\v':
        case '\f':
        r = 1;
    }
    return r;
}

unsigned char getval(unsigned char c) {
    unsigned char r = 16;
    for (int i = 0; i < 22; i++)
        if (c == nibbles[i][0]) {
            r = nibbles[i][1];
            break;
        }
    return r;
}

void close_file(FILE *f, const char *filename, int del) {
    if (fclose(f))
        fprintf(stderr, "Failed to close target file '%s'.\n", filename);
    if (del)
        if (remove(filename))
            fprintf(stderr, "Failed to delete target file '%s'.\n", filename);
}
