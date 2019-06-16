#ifndef MINUNIT_H
#define MINUNIT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
extern int tests_run;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* MINUNIT_H */
