#ifndef _TABELAH_
#define _TABELAH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"
#include "Palavras.h"
#include "Significados.h"

struct Tabela {
    char significado[MAX_WORD];
    int ocorrencia;
};
typedef struct Tabela TABELA;
typedef TABELA * PTABELA;

int criaTabela2(PPALAVRA p, PSIGNIFICADOS ptr){
    PSPALAVRAS a;
    a = pesquisaSPalavra(ptr, cmpSPalavra, p->palavra);
    if(a){
        return p->ocorrencia;
    }
    return 0;
}

PTABELA criaTabela(PNO individuais, PSIGNIFICADOS significado){
	PNO ptr;
	PTABELA novo;
	novo = (PTABELA) malloc(sizeof(TABELA));
	int i, total = 0;
	for (ptr= individuais; ptr ; ptr = ptr -> prox){
		i = criaTabela2(ptr -> dados, significado);
		total += i;
	}
	for (i = 0; i <= strlen(significado->significado); i++){
        novo->significado[i] = significado->significado[i];
	}
	novo->ocorrencia = total;
	return novo;
}

int totalPalavras(PPALAVRA p, int total){
    return total + p->ocorrencia;
}

void imprimeTabela2(PTABELA p, int total){
    float relativa;
    relativa = (float)(p->ocorrencia*100)/total;
    printf("%s                   %d                %0.2f\%\n", p->significado, p->ocorrencia, relativa);
}

int imprimeTabela(PNO tabela, PNO individuais){
        PNO ptr;
        int total = 0;

        for(ptr=individuais; ptr; ptr=ptr->prox){
            total = totalPalavras(ptr->dados, total);
        }

        printf("\n*** Tabela de Frequencias ***\n\n");
        printf("Significado         F.Absoluta        F.Relativa\n\n");

        printf("Todos                  %d              100.00\%\n", total);

        for(ptr=tabela; ptr; ptr=ptr->prox){
            imprimeTabela2(ptr->dados, total);
        }
        return total;
}

int imprimeFora(PPALAVRA individuais, PNO cabeca){
    PNO ptr;
    int i = 1;
    for(ptr = cabeca; ptr; ptr=ptr->prox){
            i = imprimeFora2(individuais->palavra, cabeca->dados);
            if(i == 0){
                return 0;
            }
    }
    printf("   -> %s\n", individuais->palavra, individuais->ocorrencia);
    return individuais->ocorrencia;
}

int imprimeFora2(char * palavra, PSIGNIFICADOS cabeca){
    PSPALAVRAS a;
    a = pesquisaSPalavra(cabeca, cmpSPalavra, palavra);
    if(a){
        return 0;
    }
    return 1;
}

#endif
