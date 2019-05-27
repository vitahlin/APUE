#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include "./apue.h"

void LogErrQuit(string str) {
    cout << str << endl;
    exit(1);
}

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

void LogErr(string str) {
    cout << str << endl;
}

static void sig_usr(int signo) {
    sigflag = 1;
}

void TELL_WAIT() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        LogErrQuit("signal sigusr1 error");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        LogErrQuit("signal sigusr2 error");
    }

    // 将newmask信号集初始化为空，执行成功返回0，有错误返回-1
    sigemptyset(&newmask);
    sigemptyset(&zeromask);

    // 将参数SIGUSR1代表的信号加入至参数&newmark信号集里
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    // 调用该函数的进程，使用新的信号屏蔽集。newmask是我们希望阻塞的附加信号集
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        LogErrQuit("SIG_BLOCK error");
    }
}