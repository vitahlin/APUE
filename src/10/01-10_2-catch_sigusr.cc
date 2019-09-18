/**
 * 捕捉SIGUSR1和SIGUSR2信号的示例
 * 使程序在后台运行，./01-10_2-catch_sigusr & ，然后用kill命令将信号发送给进程
 */

#include "./../lib/apue.h"

static void SigUsrHandler(int);

int main(int argc, const char** argv) {
    if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR) {
        ErrorSystem("can not catch SIGUSR1");
    }

    if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR) {
        ErrorSystem("can not catch SIGUSR2");
    }

    for (;;) {
        /**
         * 使进程（或者线程）睡眠状态，直到接收到信号，要么终止，或导致它调用一个信号捕获函数
         */
        pause();
    }

    return 0;
}

static void SigUsrHandler(int sig_num) {
    if (sig_num == SIGUSR1) {
        cout << "Catch signal SIGUSR1" << endl;
    } else if (sig_num == SIGUSR2) {
        cout << "Catch signal SIGUSR2" << endl;
    } else {
        cout << "Catch signal " << sig_num << endl;
    }
}