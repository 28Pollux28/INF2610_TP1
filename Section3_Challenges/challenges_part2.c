/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part2.c
 *
 * Valentin LEMAIRE 2409221
 * Kamil MAARITE 21526203
*/
#include "challenges_part2.h"
#define MAX_THREADS 8

typedef struct {
    Matrix* A;
    Matrix* B;
    Matrix* result;
    int row;
    int end;
    int debug;
    } multiply_args;

Matrix* multiply(Matrix* A, Matrix* B) {
    // Vérifier la validité des matrices
    if(A == NULL || B == NULL || A->rows <= 0 || A->cols <= 0 || B->rows <= 0 || B->cols <= 0 || A->cols != B->rows) {
        return NULL;
    }
    // print A and B
    // printf("Matrix A:\n");
    // for(int i = 0; i < A->rows; i++) {
    //     for(int j = 0; j < A->cols; j++) {
    //         printf("%d ", A->matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("Matrix B:\n");
    // for(int i = 0; i < B->rows; i++) {
    //     for(int j = 0; j < B->cols; j++) {
    //         printf("%d ", B->matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    // Créer la matrice résultat
    Matrix* result = (Matrix*)malloc(sizeof(Matrix));

    result->rows = A->rows;
    result->cols = B->cols;

    // Tableau 2D de taille ligne * colonne
    // Allocation des lignes
    result->matrix = (short**)malloc(sizeof(short*) * result->rows);

    // Pour chaque ligne, allocation des colonnes
    for(int i = 0; i < result->rows; i++) {
        result->matrix[i] = (short*)malloc(sizeof(short) * result->cols);
    }

    // Calcul du produit
    // for(int i = 0; i < result->rows; i++) {
    //     for(int j = 0; j < result->cols; j++) {
    //         result->matrix[i][j] = 0;
    //         for(int k = 0; k < A->cols; k++) {
    //             result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    //         }
    //     }
    // }
    // printf("A size: %d x %d\n", A->rows, A->cols);
    // printf("B size: %d x %d\n", B->rows, B->cols);
    
    //utilisation de threads
    pthread_t threads[A->rows];
    for(int i = 0; i < A->rows; i+=40) {
        multiply_args* args = (multiply_args*)malloc(sizeof(multiply_args));
        args->A = A;
        args->B = B;
        args->result = result;
        args->row = i;
        args->end = (i + 40) > A->rows ? A->rows : i + 40;
        args->debug = i==A->rows+1;
        // printf("start: %d, end: %d\n", args->rows_start, args->rows_end);
        pthread_create(&threads[i], NULL, (void*(*)(void*))multiply_thread, args);
    }

    // Attente de la fin des threads
    for(int i = 0; i < A->rows; i+=40) {
        pthread_join(threads[i], NULL);
    }



    // printf("result size: %d x %d\n", result->rows, result->cols);
    // for(int i = 0; i < result->rows; i++) {
    //     for(int j = 0; j < result->cols; j++) {
    //         printf("%d ", result->matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    return result;
}

void* multiply_thread(void* args) {
    // Récupération des arguments
    multiply_args* a = (multiply_args*)args;
    Matrix* A = a->A;
    Matrix* B = a->B;
    int row = a->row;
    int end = a->end;
    Matrix* result = a->result;
    // Calcul du produit
    for(int i = row; i < end; i++) {
        for(int k = 0; k < A->cols; k++) {
            for(int j = 0; j < result->cols; j++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // int rows_start = a->rows_start;
    // int rows_end = a->rows_end;
    // Calcul du produit avec blocs
    // Calcul optimal de la taille des blocs
    // int block_size = max_block_size(30, rows_end-rows_start, B->cols);
    // if(a->debug){
    //     printf("A size: %d x %d\n", A->rows, A->cols);
    //     printf("B size: %d x %d\n", B->rows, B->cols);
    //     printf("rows_start: %d, rows_end: %d\n", rows_start, rows_end);
    //     printf("block_size: %d\n", block_size);
    // }
    


    // for(int ii = rows_start; ii < rows_end; ii+=block_size) {
    //     for(int jj = 0; jj < result->cols; jj+=block_size) {
    //         for(int kk = 0; kk < A->cols; kk += block_size) {
    //             if(a->debug) {
    //                 int i_range = min(block_size,rows_end-ii)+ii;
    //                 int j_range = min(block_size,B->cols)+jj;
    //                 int k_range = min(block_size,A->cols)+kk;
    //                 printf("i range: %d - %d\n", ii, i_range);
    //                 printf("j range: %d - %d\n", jj, j_range);
    //                 printf("k range: %d - %d\n", kk, k_range);
    //             }
    //             for(int i = 0; i < min(block_size,rows_end-ii); i++) {
    //                 for(int j = 0; j < min(block_size,B->cols-jj); j++) {
    //                     for(int k = 0; k < min(block_size,A->cols-kk); k++) {
    //                         int iii = i+ii;
    //                         int jjj = jj+j;
    //                         int kkk = k+kk;
    //                         if(a->debug){
    //                             printf("ii+i=%d, jj+j=%d, kk+k=%d, kk=%d, k=%d\n",iii,jjj,kkk,kk,k);
    //                         }
    //                         result->matrix[ii+i][jj+j] += A->matrix[ii+i][kk+k] * B->matrix[kk+k][jj+j];
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // Libération de la mémoire
    free(a);

    return NULL;
}

int max_block_size(int block_size, int rows, int cols) {
    int max_matrix_size = min(rows, cols);
    return min(max_matrix_size, block_size);
}

int min(int a, int b) {
    return a < b ? a : b;
}


// This main is to help you in your development. 
// Don't forget to comment it out when you run the tests.
// int main(int argc, char*argv[])
// {
//     Matrix* A = (Matrix*)malloc(sizeof(Matrix));
//     A->rows = 4;
//     A->cols = 4;
//     A->matrix = (short**)malloc(sizeof(short*) * A->rows);
//     for(int i = 0; i < A->rows; i++) {
//         A->matrix[i] = (short*)malloc(sizeof(short) * A->cols);
//     }
//     for(int i = 0; i < A->rows; i++) {
//         for(int j = 0; j < A->cols; j++) {
//             A->matrix[i][j] = i * A->cols + j;
//         }
//     }
//     Matrix* B = (Matrix*)malloc(sizeof(Matrix));
//     B->rows = 4;
//     B->cols = 4;
//     B->matrix = (short**)malloc(sizeof(short*) * B->rows);
//     for(int i = 0; i < B->rows; i++) {
//         B->matrix[i] = (short*)malloc(sizeof(short) * B->cols);
//     }
//     for(int i = 0; i < B->rows; i++) {
//         for(int j = 0; j < B->cols; j++) {
//             B->matrix[i][j] = i * B->cols + j;
//         }
//     }
//     Matrix* C = multiply(A, B);
//     if(C == NULL) {
//         printf("Erreur, produit matriciel invalide\n");
//         free(A->matrix);
//         free(A);
//         free(B->matrix);
//         free(B);
//         return 1;
//     }
//     for(int i = 0; i < C->rows; i++) {
//         for(int j = 0; j < C->cols; j++) {
//             printf("%d ", C->matrix[i][j]);
//         }
//         printf("\n");
//     }

//     free(A->matrix);
//     free(A);
//     free(B->matrix);
//     free(B);
//     free(C->matrix);
//     free(C);
//     return 0;
// }
