/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * SystemCalls - part1.c
 *
 * VALENTIN LEMAIRE 2409221
 * KAMIL MAARITE 2152653
*/
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const int STDINFILENUMBER = 0;

int main () {
    int fd = open("systemcalls_output2.txt", O_WRONLY | O_TRUNC);
    if(fd == -1) {
        perror("Appel système open échoué");
        return -1;
    }
    printf("Saisissez votre texte suivi de CTRL-D :\n");
    char buf;
    while(read(STDINFILENUMBER, &buf, 1) > 0){
        //handle read error TODO
        int bytes_written  = write(fd, &buf,1);
        if(bytes_written < 0){
            perror("Appel Système write échoué");
            close(fd);
            return -1;
        }
    }
    close(fd);
    return 0;
}
