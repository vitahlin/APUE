/**
 * 使用alarm和pause函数来实现sleep进程休眠功能
 *
 * 运行时执行Ctrl+C来中断程序，会发现MySleep函数引起的longjmp会使另外一个信号处理程序SigIntHandler提早终止，即使它还未完成。
 */

#include "./../lib/apue.h"

#include <setjmp.h>
#include <sys/wait.h>
#include <ctime>

static jmp_buf env_alrm;

static void SigIntHandler(int);
static void SigAlrm(int);

int MySleep(int seconds) {
    cout << "Sleep " << seconds << " seconds ..." << endl;

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        return seconds;
    }

    if (setjmp(env_alrm) == 0) {
        cout << "Set alarm" << endl;
        alarm(seconds);
        pause();
    }

    cout << "Alarm end" << endl;

    return alarm(0);
}

int main(int argc, const char** argv) {
    unsigned int unslept;

    /**
     * SIGINT程序终止信号
     */
    if (signal(SIGINT, SigIntHandler)) {
        ErrorSystem("signal(SIGINT) error");
    }

    cout << "Run begin time " << time(0) << endl;
    unslept = MySleep(5);
    cout << "Run end time " << time(0) << endl;
    cout << "MySleep returned: " << unslept << endl;

    return 0;
}

static void SigIntHandler(int sig_num) {
    cout << "SigInt start" << endl;

    int i, j;

    // 用volatile阻止优化编译程序去除循环语句
    volatile int k;

    cout << "Int handler begin time " << time(0) << endl;

    // 让循环的运行时间大于休眠时间
    for (i = 0; i < 300000; i++) {
        for (j = 0; j < 40000; j++) {
            k += i * j;
        }
    }

    cout << "Int handler end time " << time(0) << endl;
    cout << "SigInt end" << endl;
}

static void SigAlrm(int sig_num) {
    cout << "Run SigAlrm..." << endl;
    longjmp(env_alrm, 1);
}