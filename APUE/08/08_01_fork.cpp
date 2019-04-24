/**
 * fork函数，子进程对变量所做的改变并不影响父进程该变量的值。
 * fork之后父进程先执行还是子进程先执行是不确定的。这里使父进程休眠2秒，以此使子进程先执行。
 */

#include <unistd.h>
#include <iostream>
using namespace std;

int global_var = 6;
char buf[] = "a write to stdout\n";

int main(int argc, const char** agrv) {
    int var = 88;
    pid_t pid;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        cout << "write error" << endl;
        exit(0);
    }

    cout << "before fork" << endl;

    if ((pid = fork()) < 0) {
        cout << "fork error" << endl;
        exit(0);
    } else if (pid == 0) {
        // child
        global_var++;
        var++;
    } else {
        // parent
        sleep(2);
    }

    cout << "pid=" << getpid() << ", global_var=" << global_var
         << ", var=" << var << endl;

    return 0;
}
