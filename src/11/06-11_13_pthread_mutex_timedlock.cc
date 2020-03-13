/**
 * pthread_mutex_timedlock用法
 * Todo：macOS不支持该方法
 */

#include "./../lib/apue.h"

int main(int argc, const char** argv) {
    int err;

    struct timespec tout;
    struct tm* tmp;

    char buf[64];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    cout << "Mutex is locked" << endl;

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    cout << "Current time is " << buf << endl;

    tout.tv_sec += 10;

    err = pthread_mutex_timedlock(&mutex, &tout);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    cout << "The time is now " << buf << endl;
    if (err == 0) {
        cout << "Mutex locked again" << endl;
    } else {
        cout << "Can not lock mutex again: " << strerror(err) << endl;
    }

    return 0;
}