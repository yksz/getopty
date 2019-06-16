#pragma once

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct opty {
    int err;
    int ind;
    int opt;
    char* arg;

    // internal
    int pos;
};

static inline void getopty_sort(int argc, char** argv, struct opty* opty, int startindex)
{
    if (opty->pos > 1) {
        return;
    }

    int shift = opty->arg == NULL ? 1 : 2;
    int endindex = opty->ind - shift;
    char* option = argv[endindex];
    for (int i = endindex - 1; i >= startindex; i--) {
        argv[i + shift] = argv[i];
    }
    argv[startindex] = option;
    if (opty->arg != NULL) {
        argv[startindex + 1] = opty->arg;
    }
    opty->ind = startindex + shift;
}

static inline int getopty(int argc, char** argv, const char* opts, struct opty* opty)
{
    if (argc <= 0 || argv == NULL || opts == NULL || opty == NULL) {
        return -1;
    }
    if (opty->ind <= 1) {
        opty->ind = 1;
        opty->pos = 1;
    }
    if (opty->ind >= argc) {
        return -1;
    }

    // skip arguments
    int startindex = opty->ind;
    for (int i = opty->ind; i < argc; i++) {
        char* s = argv[i];
        if (s[0] == '-' && strlen(s) > 1) {
            opty->ind = i; // option found
            break;
        }
        if (i == argc - 1) { // last
            return -1; // option not found
        }
    }

    char* str = argv[opty->ind];
    size_t len = strlen(str);
    if (opty->pos >= len) {
        return -1;
    }
    char c = str[opty->pos];

    const char* subopts = NULL;
    if (c == ':' || (subopts = strchr(opts, c)) == NULL) {
        if (opty->err) {
            fprintf(stderr, "%s: illegal option -- %c\n", argv[0], c);
        }
        opty->opt = c;
        c = '?';
    }

    if (subopts == NULL || subopts[1] != ':') { // no argument
        opty->arg = NULL;
        opty->pos++;
        if (opty->pos >= len) {
            opty->ind++;
            opty->pos = 1;
        }
    } else { // required argument
        opty->ind++;
        if (opty->ind >= argc) {
            if (opty->err) {
                fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0], c);
            }
            opty->arg = NULL;
            opty->opt = c;
            c = '?';
        } else {
            opty->arg = argv[opty->ind];
            opty->ind++;
            opty->pos = 1;
        }
    }

    getopty_sort(argc, argv, opty, startindex);
    return c;
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
