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
    DIR *d;
    struct dirent *dir;
    while(1){
        label:
        d = opendir(path);
        if (d) {
            printf("PATH: %s\nDID: %d\nPDID: %d\n",path,getpid(),getppid());
            printf("FILES:\n");
            while ((dir = readdir(d)) != NULL) {
                if(dir->d_type == DT_DIR){
                    if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue; // Omit the "." and ".." folders
                    if(fork()==0){
                        strcat(path,"/");
                        strcat(path,dir->d_name);
                        goto label;
                    }
                    wait(NULL);
                } else {

                }
                //printf("%s\n", dir->d_name);
            
            }
            closedir(d);
            if(strcmp(path,ROOT_PATH) != 0){
                _exit(0);
            }
        }
        break;
        
    }
    
    return 0;
}



// pour chaque répertoire :
// on dit l'emplacement du répertoire
// on dit le n° de pid du processus
// on dit le n° du processus parent
// on liste tous les fichiers : si c'est un directory, on crée un nouveau processus et on recommence.
