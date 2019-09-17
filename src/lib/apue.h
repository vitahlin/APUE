#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include <sys/wait.h>

#include <iostream>

#include <signal.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// 错误打印函数封装，在log_err.cpp
void LogErr(string str);
void LogErrQuit(string str);

// 信号相关，tellwait.cpp
void TELL_WAIT();
void TELL_CHILD(pid_t);
void TELL_PARENT(pid_t);
void WAIT_CHILD();
void WAIT_PARENT();