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


Matrix* multiply(Matrix* A, Matrix* B) {
    // Vérifier la validité des matrices
    if(A == NULL || B == NULL || A->rows <= 0 || A->cols <= 0 || B->rows <= 0 || B->cols <= 0 || A->cols != B->rows) {
        return NULL;
    }
    
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

    //utilisation de threads
    pthread_t threads[MAX_THREADS];
    for(int i = 0; i < MAX_THREADS; i+=1) {
        multiply_args* args = (multiply_args*)malloc(sizeof(multiply_args));
        args->A = A;
        args->B = B;
        args->result = result;
        args->start = i * A->rows / MAX_THREADS;
        args->end = (i+1) * A->rows / MAX_THREADS;
        pthread_create(&threads[i], NULL, (void*(*)(void*))multiply_thread, args);
    }

    // Attente de la fin des threads
    for(int i = 0; i < MAX_THREADS; i+=1) {
        pthread_join(threads[i], NULL);
    }
    return result;
}

void* multiply_thread(void* args) {
    // Récupération des arguments
    multiply_args* a = (multiply_args*)args;
    Matrix* A = a->A;
    Matrix* B = a->B;
    int start = a->start;
    int end = a->end;
    Matrix* result = a->result;
    // Calcul du produit
    for(int i = start; i < end; i++) {
        for(int k = 0; k < A->cols; k++) {
            for(int j = 0; j < result->cols; j++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }
    
    // Libération de la mémoire
    free(a);

    return NULL;
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
