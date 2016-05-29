#ifndef _SIGNIFICADOSH_
#define _SIGNIFICADOSH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"

#define MAX_WORD 60
#define MAX_SIG 60

typedef void* PVOID;
typedef void** PPVOID;

struct Significados {
    char significado[MAX_WORD];
    PPVOID cabeca;
    int tamanho;
    int posicao;
};
typedef struct Significados SIGNIFICADOS;
typedef SIGNIFICADOS * PSIGNIFICADOS;

struct SPalavras {
    char spalavra[MAX_WORD];
};
typedef struct SPalavras SPALAVRAS;
typedef SPALAVRAS * PSPALAVRAS;

PSIGNIFICADOS criaSignificados(){
    PSIGNIFICADOS novo;
    novo = (PSIGNIFICADOS) malloc(sizeof(SIGNIFICADOS));
    printf("\nEscreva o Significado: ");
    fflush(stdout);
    fgets(novo->significado, MAX_WORD, stdin);
    letraMinusculas(novo->significado);
    //strlwr(novo->significado);
    novo->significado[strlen(novo->significado)-1] = '\0';
    novo->cabeca = (PPVOID)malloc(sizeof(PVOID) * MAX_SIG);
    novo->tamanho = MAX_SIG;
    novo->posicao = 0;
    return novo;
}

int cmpSignificado(PSIGNIFICADOS a, char* palavra){
    return strcmp(a->significado, palavra) == 0;
}

void imprimeSignificados(PSIGNIFICADOS p, PNO ptr){
    if(ptr->ant == NULL){
        printf("\nSignificados:\n\n");
    }
    printf("   -> %s\n", p->significado);
}

//----------------------------------------------------------------------------------------

PSPALAVRAS criaSPalavra(){
    PSPALAVRAS novo;
    novo = (PSPALAVRAS) malloc(sizeof(SPALAVRAS));
    printf("\nEscreva a Palavra: ");
    fflush(stdout);
    fgets(novo->spalavra, MAX_WORD, stdin);
    letraMinusculas(novo->spalavra);
    //strlwr(novo->spalavra);
    novo->spalavra[strlen(novo->spalavra)-1] = '\0';
    return novo;
}

//Insere palavra no fim do vetor
void insereSPalavra(PSIGNIFICADOS l, PVOID dados){
    if(l->posicao >= l->tamanho){
        l->cabeca = (PPVOID)realloc( l->cabeca, sizeof(PVOID) * (l->tamanho + MAX_SIG));
        l->tamanho += MAX_SIG;
    }
    l->cabeca[l->posicao] = dados;
    l->posicao++;
}

//Imprime o vetor

void imprimeSPalavra(PSIGNIFICADOS l, void (*print)()){
    int i;
    for(i=0; i< l->posicao; i++){
            (*print)(l->cabeca[i]);
    }
}

void imprimeSPalavra2(PSPALAVRAS a){
    printf("   -> %s\n", a->spalavra);
}

void* pesquisaSPalavra(PSIGNIFICADOS l, int (*compara)(), void* valor){
    int i;
    for( i=0; i < l->posicao; i++){
        if((*compara)(l->cabeca[i], valor)){
            return l->cabeca[i];
        }
    }
    return NULL;
}

int cmpSPalavra(PSPALAVRAS a, char* palavra_tmp){
    return strcmp(a->spalavra, palavra_tmp) == 0;
}

    // funçao auxiliar de remoçao
void RemoveIndiceSPalavra (PSIGNIFICADOS l, int p) {
    int i;
    free(l -> cabeca[p]);
    for (i = p; i < l -> posicao - 1; i++){
        l -> cabeca[i] = l -> cabeca[i+1];
    }
    l -> posicao --;
}

    // funçao de remoçao
int  removerSPalavra(PSIGNIFICADOS l, int (*compara)(), void* valor){
    int i;
    for (i=0 ; i < l -> posicao ; i++){
        if ((*compara)(l -> cabeca[i], valor)){
            RemoveIndiceSPalavra(l, i);
            return 1;
        }
    }
    return 0;
}

#endif
