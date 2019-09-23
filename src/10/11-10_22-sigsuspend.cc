/**
 * sigsuspend的用法，保护代码临界区，使其不被特定信号中断
 */

#include "./../lib/apue.h"

void PrintMask(const char* str);
static void SigInt(int);
static void SigUsr1(int);

int main(int argc, const char** argv) {
    sigset_t new_mask, old_mask, wait_mask;

    PrintMask("program start:");

    // 捕捉SIGINT信号
    if (signal(SIGINT, SigInt) == SIG_ERR) {
        ErrorSystem("signal(SIGINT) error");
    }

    // 捕捉SIGINT信号
    if (signal(SIGUSR1, SigUsr1) == SIG_ERR) {
        ErrorSystem("signal(SIGUSR) error");
    }

    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGUSR1);
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

    // 将SIGINT信号阻塞，同时保存当前信号集
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }

    PrintMask(" in critical region: ");

    /**
     * 临界区代码执行
     */

    /**
     * sigsuspend的原子操作是：
     * 1. 设置新的mask阻塞当前进程，这里是用wait替换new，即阻塞SIGUSR1信号
     * 2. 收到SIGUSR1信号，阻塞，程序继续挂起；收到其他信号，恢复原先的mask
     * 3.
     * 调用该进程设置的信号处理函数（程序中如果先来SIGUSR1信号，然后过来SIGINT信号，则信号处理函数会调用两次，第一次执行SigInt，第二次执行SigUsr1，因为SigUsr1是前面阻塞的）
     * 4.
     * 待信号处理函数返回，sigsuspend返回了（sigsuspend将捕捉信号和信号处理函数集成到一起了）
     *
     * sigsuspend实际是将sigprocmask和pause结合起来原子操作
     */
    if (sigsuspend(&wait_mask) != -1) {
        ErrorSystem("sigsuspend error");
    }

    PrintMask("after return from sigsuspend: ");

    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_MASK error");
    }

    PrintMask("program exit: ");

    return 0;
}

// 信号处理函数的实现
static void SigInt(int sig_num) {
    PrintMask("\nin sig_int: ");
}

static void SigUsr1(int sig_num) {
    cout << "catch SIGUSR1" << endl;
}

void PrintMask(const char* str) {
    sigset_t sigset;
    int errno_save;

    errno_save = errno;

    if (sigprocmask(0, NULL, &sigset) < 0) {
        ErrorReturn("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT)) {
            printf(" SIGINT");
        }

        if (sigismember(&sigset, SIGQUIT)) {
            printf(" SIGQUIT");
        }

        if (sigismember(&sigset, SIGUSR1)) {
            printf(" SIGUSR1");
        }

        if (sigismember(&sigset, SIGALRM)) {
            printf(" SIGALRM");
        }

        printf("\n");
    }

    errno = errno_save;
}