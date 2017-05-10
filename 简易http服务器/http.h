#ifndef _HTTP
#define _HTTP
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "co_routine.h"
#include "coctx.h"
#include "co_routine_inner.h"
#include <dlfcn.h>
#define SIZE 2048
#define FILE "log.txt"
#define PORT 8888
#include <stack>
using namespace std;

int init_fd(int, char*);

void *handler_in(void *);

void printf_log(string);

struct task_t{

    stCoRoutine_t *co;
    int fd;
};

#endif //_HTTP_H


