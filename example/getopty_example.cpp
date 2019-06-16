#include "getopty.h"

int main(int argc, char** argv) {
    struct opty opty = {0};
    int opt;
    while ((opt = getopty(argc, argv, "ab:", &opty)) != -1) {
        switch (opt) {
            case 'a':
                printf("opt: a\n");
                break;

            case 'b':
                printf("opt: b=%s\n", opty.arg);
                break;

            default: // '?'
                break;
        }
    }

    for (int i = opty.ind; i < argc; i++) {
        printf("arg: %s\n", argv[i]);
    }

    return 0;
}
