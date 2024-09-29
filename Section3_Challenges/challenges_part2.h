#ifndef _MULTIPLY_MATRICES
#define _MULTIPLY_MATRICES
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
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdbool.h>

typedef struct {
    short** matrix;
    short rows;
    short cols;
} Matrix;

typedef struct {
    Matrix* A;
    Matrix* B;
    Matrix* result;
    int start;
    int end;
    int debug;
    } multiply_args;

Matrix* multiply(Matrix* A, Matrix* B);
void* multiply_thread(void* args);

#endif