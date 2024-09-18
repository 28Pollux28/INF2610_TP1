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
#define nb 8

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void* p)
{
  int n0 = *((int*) p);
  long s = 0; 
  for(long i=(n0*(m/(long)nb)+1);i<=(n0+1)*m/(long)nb;i++){
    s += i;
  }
  somme[n0] = s;
  return NULL;
}


void question2( )
{
    pthread_t thr[nb];
    int values[nb];
    for(int i=0;i<nb;i++){
      values[i]=i;
      pthread_create(&thr[i], NULL, contribution, &values[i]);

    }

    for(int i =0;i<nb;i++){
      pthread_join(thr[i],NULL);
    }
    long somme_totale = 0;
    for(int i =0;i<nb;i++){
      somme_totale += somme[i];
    }
    long somme_reelle=((long)m)*(m+1)/2;
    printf("Somme totale calculée = %ld, Somme totale réelle = %ld\n",somme_totale,somme_reelle);
}

