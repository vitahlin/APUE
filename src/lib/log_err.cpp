#include "./apue.h"

void LogErrQuit(string str) {
    cout << str << endl;
    exit(1);
}

void LogErr(string str) {
    cout << str << endl;
}
