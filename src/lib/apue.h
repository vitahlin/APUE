#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAXLINE 4096

// macOS上面可能会出现SIGCLD找不到的情况
#ifndef SIGCLD
#define SIGCLD SIGCHLD
#endif

#ifdef __APPLE__

#ifndef PTHREAD_BARRIER_H_
#define PTHREAD_BARRIER_H_

typedef int pthread_barrierattr_t;
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t* barrier,
                         const pthread_barrierattr_t* attr,
                         unsigned int count) {
    if (count == 0) {
        errno = EINVAL;
        return -1;
    }
    if (pthread_mutex_init(&barrier->mutex, 0) < 0) {
        return -1;
    }
    if (pthread_cond_init(&barrier->cond, 0) < 0) {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }
    barrier->tripCount = count;
    barrier->count = 0;

    return 0;
}

int pthread_barrier_destroy(pthread_barrier_t* barrier) {
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
}

int pthread_barrier_wait(pthread_barrier_t* barrier) {
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);
    if (barrier->count >= barrier->tripCount) {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 1;
    } else {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
}

#endif  // PTHREAD_BARRIER_H_
#endif  // __APPLE__

// 错误打印函数封装，在log_err.cpp
void ErrorSystem(const char* fmt, ...);
void ErrorQuit(const char* fmt, ...);
void ErrorReturn(const char* fmt, ...);

// 信号相关，tellwait.cpp
void TELL_WAIT();
void TELL_CHILD(pid_t);
void TELL_PARENT(pid_t);
void WAIT_CHILD();
void WAIT_PARENT();

int MySystem(const char*);

void PrintExit(int status);