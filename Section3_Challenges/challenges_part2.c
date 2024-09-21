/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part2.c
 *
 * Valentin LEMAIRE 2409221
 * Kamil MAARITE 2152653
*/
#include "challenges_part2.h"

Matrix* multiply(Matrix* A, Matrix* B) {
    // Vérifier la validité des matrices
    if(A == NULL || B == NULL || A->cols != B->rows) {
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

    // Calcul du produit
    for(int i = 0; i < result->rows; i++) {
        for(int j = 0; j < result->cols; j++) {
            result->matrix[i][j] = 0;
            for(int k = 0; k < A->cols; k++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }

    return result;
}


// This main is to help you in your development. 
// Don't forget to comment it out when you run the tests.
// int main(int argc, char*argv[])
// {
//     Matrix* A = (Matrix*)malloc(sizeof(Matrix));
//     A->rows = 2;
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
//     B->rows = 3;
//     B->cols = 2;
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
