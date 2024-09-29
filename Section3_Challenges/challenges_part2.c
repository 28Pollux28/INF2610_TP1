#include "challenges_part2.h"
#define MAX_THREADS 8
#define BLOCK_SIZE 64

typedef struct {
    Matrix* A;
    Matrix* B;
    Matrix* C;
    int i_start, i_end;
    int j_start, j_end;
    int k_start, k_end;
} ThreadArgs;

void* multiply_block(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    Matrix *A = args->A, *B = args->B, *C = args->C;
    
    for (int i = args->i_start; i < args->i_end; i += BLOCK_SIZE) {
        for (int j = args->j_start; j < args->j_end; j += BLOCK_SIZE) {
            for (int k = args->k_start; k < args->k_end; k += BLOCK_SIZE) {
                // Multiply block
                for (int ii = i; ii < i + BLOCK_SIZE && ii < args->i_end; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < args->j_end; jj++) {
                        for (int kk = k; kk < k + BLOCK_SIZE && kk < args->k_end; kk++) {
                            C->matrix[ii][jj] += A->matrix[ii][kk] * B->matrix[kk][jj];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

Matrix* multiply(Matrix* A, Matrix* B) {
    if (A->cols != B->rows) {
        printf("Error: Incompatible matrix dimensions\n");
        return NULL;
    }

    Matrix* C = (Matrix*)malloc(sizeof(Matrix));
    C->rows = A->rows;
    C->cols = B->cols;
    C->matrix = (short**)calloc(C->rows, sizeof(short*));
    for (int i = 0; i < C->rows; i++) {
        C->matrix[i] = (short*)calloc(C->cols, sizeof(short));
    }

    int num_threads = MAX_THREADS;
    pthread_t threads[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS];

    int rows_per_thread = (A->rows + num_threads - 1) / num_threads;

    for (int t = 0; t < num_threads; t++) {
        thread_args[t].A = A;
        thread_args[t].B = B;
        thread_args[t].C = C;
        thread_args[t].i_start = t * rows_per_thread;
        thread_args[t].i_end = (t + 1) * rows_per_thread;
        if (thread_args[t].i_end > A->rows) thread_args[t].i_end = A->rows;
        thread_args[t].j_start = 0;
        thread_args[t].j_end = B->cols;
        thread_args[t].k_start = 0;
        thread_args[t].k_end = A->cols;

        pthread_create(&threads[t], NULL, multiply_block, &thread_args[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    return C;
}