/**
 * 竞争条件示例
 *
 * 一个由子进程输出，一个由父进程输出。因为输出依赖于内核使这两个进程运行的顺序及每个进程运行的时间长度
 * 所以该程序包含一个竞争条件。
 */

#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
using namespace std;

static void output(char* str) {
    char* ptr;
    int c;

    // 取消输出缓存
    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++) != 0;) {
        putc(c, stdout);
    }
}

int main(int argc, const char** agrv) {
    pid_t pid;

    char child_str[] = "output from child\n";
    char parent_str[] = "output from parent\n";

    if ((pid = fork()) < 0) {
        cout << "fork error" << endl;
        exit(0);
    } else if (pid == 0) {
        output(child_str);
    } else {
        output(parent_str);
    }
    return 0;
}
