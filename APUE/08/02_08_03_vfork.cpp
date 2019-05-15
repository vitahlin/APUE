/**
 * vfork函数，子进程改变了父进程中的变量值，因为子进程在父进程的地址空间中运行
 */

#include <unistd.h>
#include <iostream>
using namespace std;

int global_var = 6;

int main(int argc, const char** agrv) {
    int var = 88;
    pid_t pid;

    cout << "before fork" << endl;

    if ((pid = vfork()) < 0) {
        cout << "fork error" << endl;
        exit(0);
    } else if (pid == 0) {
        global_var++;
        var++;
        _exit(0);
    }

    cout << "pid=" << getpid() << ", global_var=" << global_var
         << ", var=" << var << endl;

    return 0;
}
