#ifndef _GENERICH_
#define _GENERICH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// No de ligaçao
struct no {
	struct no * prox;
	struct no * ant;
	void * dados;
};
typedef struct no NO;
typedef NO * PNO;
typedef NO ** PPNO;

// inserir no incio
void InserInicio (PPNO cabeca, void * dados){

	PNO novo;
	novo= (PNO)malloc(sizeof(NO));
	if (*cabeca) (*cabeca)-> ant = novo;
	novo -> prox = *cabeca;
	novo -> ant = NULL;
	*cabeca = novo;
	novo -> dados = dados;
}

//inserir no fim
void InserFim(PPNO cabeca, void * dados){
	PNO ptr, novo;
	if (!*cabeca){
		InserInicio(cabeca, dados);
	}else{
		for (ptr = *cabeca; ptr -> prox; ptr= ptr->prox);
        novo = (PNO)malloc(sizeof(NO));
        ptr -> prox = novo;
        novo -> prox = NULL;
        novo -> ant = ptr;
        novo -> dados = dados;
	}
}

void Imprime(PNO cabeca, void (*ImprimeDados)()){

	PNO ptr;
	for (ptr= cabeca; ptr ; ptr = ptr -> prox){
		(*ImprimeDados) (ptr -> dados, ptr);
	}
	getchar();
}

// funçao generica de pesquisa
void* pesquisa (PNO cabeca, int (*compara)(), void* valor){
	PNO ptr;
	for (ptr = cabeca; ptr ; ptr = ptr -> prox){
		if ((*compara)(ptr -> dados, valor)){
			return ptr->dados;
		}
	}
	return NULL;
}

int Remover (PPNO cabeca, int (*compara)(), void* valor){

    PNO ptr;
    for (ptr = *cabeca; ptr ; ptr = ptr -> prox){
        if ((*compara)(ptr -> dados, valor)){
            if (ptr -> ant){
                ptr -> ant -> prox = ptr -> prox;
            }else{
                *cabeca = ptr -> prox;
            }
            if (ptr -> prox){
                ptr -> prox -> ant = ptr -> ant;
            }
            free(ptr -> dados);
            free(ptr);
            return 1;
        }
    }
    return 0;
}

char* letraMinusculas(char * palavra){
    int i;
    for(i = 0; i < strlen(palavra); i++){
        if( palavra[i]  >= 'A' && palavra[i]  <= 'Z'){
            palavra[i] += 32;
        }
    }
    return palavra;
}

#endif

