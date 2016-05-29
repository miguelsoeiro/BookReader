#ifndef _PALAVRASH_
#define _PALAVRASH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"
#include "Linhas.h"

#define MAX_WORD 60

struct Palavra {
    char palavra[MAX_WORD];
    int ocorrencia;
};
typedef struct Palavra PALAVRA;
typedef PALAVRA * PPALAVRA;

int cmpPalavra(PPALAVRA a, char* palavra){
    return strcmp(a->palavra, palavra) == 0;
}

void imprimePalavras(PPALAVRA p, PNO ptr){
    printf("   %d - %s\n", p->ocorrencia, p->palavra);
    if(ptr->prox==NULL){
        printf("\nPressione ENTER para continuar...");
    }
}

#endif
