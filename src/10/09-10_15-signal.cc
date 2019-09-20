/**
 */

#include "./../lib/apue.h"

static void SigQuitHandler(int);

int main(int argc, const char** argv) {
    sigset_t new_mask, old_mask, pend_mask;

    if (signal(SIGQUIT, SigQuitHandler) == SIG_ERR) {
        ErrorSystem("can not reset SIGQUIT");
    }

    // 初始化new_mask，信号集里面的所有信号被清空
    sigemptyset(&new_mask);

    // 将SIGQUIT信号加入到new_mask信号集
    sigaddset(&new_mask, SIGQUIT);

    /**
     * 调用sigprocmask可以检测或者更改信号屏蔽字，
     * 如果old_mask是非空指针，那么进程当前的信号屏蔽字通过old_mask返回
     * 如果new_mask是一个指针，第一个参数指示如何修改当前信号屏蔽字
     *
     * SIG_BLOCK 该进程新的信号屏蔽字是其当前信号屏蔽字和new_mask信号集的并集
     */
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }

    sleep(5);

    /**
     * sigpengding函数返回信号集，其中的各个信号对于调用进程是阻塞的而不能递送，因而也一定是当前未决的
     * 该信号集通过peng_mask参数返回，成功返回0，失败返回-1
     */
    if (sigpending(&pend_mask) < 0) {
        ErrorSystem("sigpending error");
    }

    /**
     * 信号集里面有该信号则返回1，没有则返回0，有错误则返回-1
     */
    if (sigismember(&pend_mask, SIGQUIT)) {
        cout << "SIGQUIT pending" << endl;
    }

    /**
     * SIG_SETMASK 将old_mask信号集设置为信号掩码
     */
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_SETMASK error");
    }

    cout << "SIGQUIT unblocked" << endl;

    sleep(5);

    return 0;
}

static void SigQuitHandler(int sig_num) {
    cout << "catch SIGQUIT" << endl;

    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        ErrorSystem("can not reset SIGQUIT");
    }
}