#ifndef _LINHASH_
#define _LINHASH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"

#define MAX_LINE 100

struct Linha {
    char linha[MAX_LINE];
};
typedef struct Linha LINHA;
typedef LINHA * PLINHA;

//Imprime lista toda
void imprimeTodaLinha(PLINHA p, PNO ptr){
    if(ptr->ant == NULL){
            printf("\nTodas as linhas:\n\n");
    }
    printf("   %s\n", p->linha);
    if(ptr->prox==NULL){
        printf("\nPressione ENTER para continuar...");
    }
}

//Imprime lista sequencialmente
void imprimeVezLinha(PLINHA p, PNO ptr){
    if(ptr->ant == NULL){
        printf("\nPressiona ENTER para mostrar a linha sequinte.\n\n");
    }
    printf("   %s\n", p->linha);
    getchar();
    if(ptr->prox==NULL){
        printf("\nNao existe mais linhas\n");
    }
}

#endif
