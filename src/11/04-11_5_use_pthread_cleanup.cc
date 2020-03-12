/**
 * 线程清理处理程序
 *
 * Todo：修正代码，使之编译通过
 *
 * 在macOS和Centos7上编译都失败，书上说明运行结果：
 * thread 1 start
 * thread 1 push complete
 * thread 2 start
 * thread 2 push complete
 * cleanup: thread 2 second handler
 * cleanup: thread 2 first handler
 * thread 1 exit code 1
 * thread 2 exit code 2
 *
 * 两个线程都正确的启动和退出，但是只有线程2的清理处理程序被调用了。
 * 因此如果线程是通过从它的启动例程中返回而终止的化，它的清理处理程序
 * 就不会被调用。同时，清理处理程序是按照与它们安装时相反的顺序被调用。
 */

#include "./../lib/apue.h"

void Cleanup(void* arg) {
    printf("cleanup: %s\n", (char*)arg);
}

void* ThreadFunc1(void* arg) {
    cout << "thread 1 start" << endl;
    pthread_cleanup_push(Cleanup, "thread 1 first handler");
    pthread_cleanup_push(Cleanup, "thread 1 second handler");
    cout << "thread 1 push complete" << endl;

    if (arg) {
        return ((void*)1);
    }

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void*)1);
}

void* ThreadFunc2(void* arg) {
    cout << "thread 2 start" << endl;
    pthread_cleanup_push(Cleanup, "thread 2 first handler");
    pthread_cleanup_push(Cleanup, "thread 2 second handler");
    cout << "thread 2 push complete" << endl;

    if (arg) {
        return ((void*)2);
    }

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main(int argc, const char** argv) {
    pthread_t tid_1, tid_2;
    int err;
    void* tret;

    // 创建线程1
    err = pthread_create(&tid_1, NULL, ThreadFunc1, (void*)1);
    if (err != 0) {
        ErrorQuit("can not create thread 1");
    }

    // 创建线程2
    err = pthread_create(&tid_2, NULL, ThreadFunc2, (void*)1);
    if (err != 0) {
        ErrorQuit("can not create thread 2");
    }

    err = pthread_join(tid_1, &tret);
    if (err != 0) {
        ErrorQuit("can not join with thread 1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);

    err = pthread_join(tid_2, &tret);
    if (err != 0) {
        ErrorQuit("can not join with thread 2");
    }
    printf("thread 2 exit code %ld\n", (long)tret);

    return 0;
}