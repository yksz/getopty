#include <stdio.h>
#include "getopty.h"
#include "minunit.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

int tests_run = 0;

static char* test_getopty_base()
{
    char* argv[] = { "a.out", "-x", "-a", "-b", "opt", "-cd", "arg1", "arg2" };
    int argc = LEN(argv);

    struct opty opty = {0};
    int opt;
    while ((opt = getopty(argc, argv, "ab:cd", &opty)) != -1) {
        printf("-%c: %s\n", opt, opty.arg);
        switch (opt) {
            case 'a':
                mu_assert("-a option: opty.arg != NULL", opty.arg == NULL);
                break;

            case 'b':
                mu_assert("-b option: opty.arg != \"opt\"", strcmp("opt", opty.arg) == 0);
                break;

            case 'c':
                mu_assert("-c option: opty.arg != NULL", opty.arg == NULL);
                break;

            case 'd':
                mu_assert("-d option: opty.arg != NULL", opty.arg == NULL);
                break;

            default: // '?'
                mu_assert("-? option: opty.opt != 'x'", opty.opt == 'x');
                break;
        }
    }
    mu_assert("opty.ind != argc - 2", opty.ind == argc - 2);
    mu_assert("argv[opty.ind + 0] != \"arg1\"", strcmp("arg1", argv[opty.ind + 0]) == 0);
    mu_assert("argv[opty.ind + 1] != \"arg2\"", strcmp("arg2", argv[opty.ind + 1]) == 0);

    return 0;
}

static char* test_getopty_sort()
{
    char* argv[] = { "a.out", "arg1", "-a", "arg2", "arg3", "-b", "opt", "arg4" };
    int argc = LEN(argv);

    struct opty opty = {0};
    int opt;
    while ((opt = getopty(argc, argv, "ab:cd", &opty)) != -1) {
        printf("-%c: %s\n", opt, opty.arg);
        switch (opt) {
            case 'a':
                mu_assert("-a option: opty.arg != NULL", opty.arg == NULL);
                break;

            case 'b':
                mu_assert("-b option: opty.arg != \"opt\"", strcmp("opt", opty.arg) == 0);
                break;

            default: // '?'
                break;
        }
    }
    mu_assert("opty.ind != argc - 4", opty.ind == argc - 4);
    mu_assert("argv[opty.ind + 0] != \"arg1\"", strcmp("arg1", argv[opty.ind + 0]) == 0);
    mu_assert("argv[opty.ind + 1] != \"arg2\"", strcmp("arg2", argv[opty.ind + 1]) == 0);
    mu_assert("argv[opty.ind + 2] != \"arg3\"", strcmp("arg3", argv[opty.ind + 2]) == 0);
    mu_assert("argv[opty.ind + 3] != \"arg4\"", strcmp("arg4", argv[opty.ind + 3]) == 0);

    return 0;
}

static char* all_tests()
{
    printf("test_getopty_base - start\n");
    mu_run_test(test_getopty_base);
    printf("test_getopty_sort - start\n");
    mu_run_test(test_getopty_sort);
    return 0;
}

int main(int argc, char** argv)
{
    char* result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
