/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part1.c
 *
 * Valentin LEMAIRE 2409221
 * Kamil MAARITE 2152653
*/
#include "challenges_part1.h"
#define ROOT_PATH "./root"


int main(int argc, char*argv[])
{
    char path[MAX_PATH_LENGTH]= ROOT_PATH;
    int nombre_fichier_texte;
    while(1){
        struct dirent **namelist;
        int n;
        label:
        nombre_fichier_texte = 0;
        n = scandir(path, &namelist, NULL, alphasort);
        if (n == -1) {
            perror("scandir");
            exit(-1);
        }
        // namelist[n-1] = "." and namelist[n-2] = ".."
        printf("PATH: %s\nDID: %lu\nPDID: %lu\n",path, namelist[n-1]->d_ino, namelist[n-2]->d_ino);
        printf("FILES:\n");
        while (n--) {
            if(namelist[n]->d_type == DT_DIR){
                if(strcmp(namelist[n]->d_name,".") == 0 || strcmp(namelist[n]->d_name,"..") == 0){
                    free(namelist[n]);
                    continue;
                };
                if(fork()==0){
                    strcat(path,"/");
                    strcat(path,namelist[n]->d_name);
                    goto label;
                }
                int status;
                wait(&status);
                nombre_fichier_texte += WEXITSTATUS(status);
            } else {
                nombre_fichier_texte++;
                printf("%s\n", namelist[n]->d_name);
            }
            free(namelist[n]);
        }
        break;
        
    }
    if(strcmp(path,ROOT_PATH) == 0){
        printf("Nombre de fichiers texte: %d\n", nombre_fichier_texte);
        return 0;
    }
    
    return nombre_fichier_texte;
}



// pour chaque répertoire :
// on dit l'emplacement du répertoire
// on dit le n° de pid du processus
// on dit le n° du processus parent
// on liste tous les fichiers : si c'est un directory, on crée un nouveau processus et on recommence.
