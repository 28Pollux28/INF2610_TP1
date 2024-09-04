/*
 * Ecole Polytechnique Montreal - GIGLL
 * Automne 2024
 * SystemCalls - part2.c
 *
 * VALENTIN LEMAIRE 2409221
 * KAMIL MAARITE 2152653
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void part21 ()
{
    //77dbcb01f571f1c32s196c3a7d27f62e (printed using printf)
    //77dbcb01f571f1c32s196c3a7d27f62e (printed using write)\n
    char printfStr[]="77dbcb01f571f1c32s196c3a7d27f62e (printed using printf)";
    for(int i =0; i < strlen(printfStr);i++){
        printf(*printfStr[i]);
    }
    printf("\n");

}

void part22 ()
{
    // TODO
    
}

int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}
