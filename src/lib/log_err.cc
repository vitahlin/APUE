#include "./apue.h"

static void ErrorDoIt(int, const char*, va_list);

void ErrorSystem(const char* fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    ErrorDoIt(1, fmt, ap);
    va_end(ap);
    exit(1);
}

void ErrorQuit(const char* fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    ErrorDoIt(0, fmt, ap);
    va_end(ap);
    exit(1);
}

static void ErrorDoIt(int errnoflag, const char* fmt, va_list ap) {
    int errno_save;
    char buf[MAXLINE];

    errno_save = errno;
    vsprintf(buf, fmt, ap);

    if (errnoflag) {
        sprintf(buf + strlen(buf), ": %s", strerror(errno_save));
    }

    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
    return;
}