/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"


void question1()
{
    // Level 0
    int n = 0;
    registerProc(getpid(),getppid(),0,0);
    if(fork()==0){
        // Level 1.1
        int n1=0;
        registerProc(getpid(),getppid(),1,1);
        if(fork()==0){
            // Level 2.1
            registerProc(getpid(),getppid(),2,1);
            _exit(0);
        }
        n1+=1;
        int s;
        wait(&s);
        n1+= WEXITSTATUS(s);
        _exit(n1);
    }
    n+=1;
    if(fork()==0){
        // Level 1.2
        int n2 = 0;
        registerProc(getpid(),getppid(),1,2);
        if(fork()==0){
            // Level 2.2
            registerProc(getpid(),getppid(),2,2);
            _exit(0);
        }
        n2+=1;
        if(fork()==0){
            // Level 2.3
            registerProc(getpid(),getppid(),2,3);
            _exit(0);
        }
        n2+=1;
        int s;
        while(wait(&s) > 0){
            n2+=WEXITSTATUS(s);
        }
        _exit(n2);
    }
    n+=1;
    if(fork()==0){
        // Level 1.3
        int n3 = 0;
        registerProc(getpid(),getppid(),1,3);
        if(fork()==0){
            // Level 2.4
            registerProc(getpid(),getppid(),2,4);
            _exit(0);
        }
        n3+=1;
        int s;
        wait(&s);
        n3+=WEXITSTATUS(s);
        _exit(n3);
    }
    n+=1;
    if(fork()==0){
        // Level 1.4
        int n4 = 0;
        registerProc(getpid(),getppid(),1,4);
        if(fork()==0){
            // Level 2.5
            registerProc(getpid(),getppid(),2,5);
            _exit(0);
        }
        n4+=1;
        if(fork()==0){
            // Level 2.6
            registerProc(getpid(),getppid(),2,6);
            _exit(0);
        }
        n4+=1;
        if(fork()==0){
            // Level 2.7
            registerProc(getpid(),getppid(),2,7);
            _exit(0);
        }
        n4+=1;
        int s;
        while(wait(&s) > 0){
            n4+=WEXITSTATUS(s);
        }
        _exit(n4);
    }
    n+=1;
    int s;
    while(wait(&s) > 0){
        n+=WEXITSTATUS(s);
    }
    printf("Total de descendants créés = %d\n",n);
    printProcRegistrations();
    execlp("ls","ls","-l",NULL);
}

