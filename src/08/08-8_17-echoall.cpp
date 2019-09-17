/**
 * 回显所有命令行参数和及全部环境表
 */

#include "./../lib/apue.h"

int main(int argc, const char** argv) {
    int i;
    char** ptr;
    extern char** environ;

    for (i = 0; i < argc; i++) {
        cout << "argv[" << i << "]" << argv[i] << endl;
    }

    for (ptr = environ; *ptr != 0; ptr++) {
        cout << *ptr << endl;
    }

    return 0;
}
