/**
 * 习题8.6
 * 编写一个程序创建一个僵死进程，然后调用system执行ps(l)命令以验证该进程是僵死进程
 */

#include "./../lib/apue.h"

int main(int argc, const char** argv) {
    pid_t pid;

    int status;

    cout << "习题8.6" << endl
         << "编写一个程序创建一个僵死进程，然后调用system函数执行ps命令以验"
            "证该进程是僵死进程。"
         << endl;

    if ((pid = fork()) < 0) {
        ErrorQuit("Fork error");
    } else if (pid == 0) {
        exit(0);
    }

    cout << "Child process pid " << pid << endl;
    if ((status = MySystem("ps -el")) < 0) {
        ErrorSystem("MySystem error");
    }

    return 0;
}
