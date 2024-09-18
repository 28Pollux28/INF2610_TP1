/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 4

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void* p)
{
  printf("Hello %d\n",*((int*) p));

  return NULL;
}


void question2( )
{
    pthread_t n;
    for(int i=0;i<nb;i++){
      printf("test %d\n",i);
      pthread_create(&n, NULL, contribution, &i);
    }
    
    
}

