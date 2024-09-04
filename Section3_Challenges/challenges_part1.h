#ifndef _PROCESS
#define _PROCESS
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>

typedef struct dirent dirent;
#define MAX_PATH_LENGTH 4096
#endif