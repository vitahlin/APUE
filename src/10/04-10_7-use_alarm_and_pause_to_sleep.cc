/**
 * 使用alarm和pause函数来实现sleep进程休眠功能
 */

#include <sys/wait.h>
#include "./../lib/apue.h"

#include <ctime>

static void SigAlrm(int);

int MySleep(int seconds) {
    cout << "Sleep " << seconds << " seconds ..." << endl;

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        return seconds;
    }

    cout << "Set alarm" << endl;
    alarm(seconds);

    /**
     * pause()韩式使调用进程挂起直至捕捉到一个信号
     * 只有执行了一个信号处理程序并从其返回时，pause才返回，在这种情况下，pause返回-1，error设置为EINTR
     */
    pause();

    cout << "Alarm end" << endl;

    // alarm(0)可以取消闹钟，并返回剩余时间
    return alarm(0);
}

int main(int argc, const char** argv) {
    cout << "Run begin time " << time(0) << endl;
    MySleep(3);
    cout << "Run end time " << time(0) << endl;

    return 0;
}

static void SigAlrm(int sig_num) {
    // 不做任何事情，只是单纯调用触发pause函数
    cout << "Run SigAlrm..." << endl;
}