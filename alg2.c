
//v1 Leitura do ficheiro* e funçoes relacionadas com linhas
//*A ideia era o Programa pedir o nome do ficheiro ao utilizador mas como tive problemas, resolvi anvançar e resolver mais tarde
//**O programa le o ficheiro pg3199.txt, se pretendem ler outro ficheiro basta alterar onde diz pg3199.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"
#include "Linhas.h"
#include "Palavras.h"
#include "Significados.h"
#include "Tabela.h"

int main() {

    FILE *file;
    char fileName[MAX_WORD];

    PNO ptr = NULL;//----------------------------------------------falta acresentar

    PNO linha = NULL;
    PLINHA ptrLinha;

    PNO palavra = NULL;
    PPALAVRA ptrpalavra;
    PPALAVRA ptrpalavra2;

    PNO significados = NULL;
    PSIGNIFICADOS ptrSignifica;
    PSIGNIFICADOS ptrSignifica2;

    PSPALAVRAS ptrSPalavra;
    PSPALAVRAS ptrSPalavra2;

    int i, k, opcao1, opcao2;
    char palavra_tmp[MAX_WORD];

    //Pede o Nome do Ficheiro e e lê MAX__LINE carateres diferentes de '\n'
    printf("\nEscreva o nome do ficheiro TXT: ");

    fgets( fileName, MAX_WORD, stdin);
    fileName[strlen(fileName) - 1] = '\0';

    file = fopen(fileName, "r");
    if (file == NULL){ //Caso o ficheiro na exista
        printf("\nERRO, nao foi possivel ler o ficheiro %s", fileName);
        getchar();
        return 0;
    } else {
        ptrLinha = (PLINHA)malloc(sizeof(LINHA));
        while ((fgets(ptrLinha->linha, MAX_LINE, file)) != NULL){
            if(ptrLinha->linha[0]!='\n'){ //Caso seja uma linha em branco (apenas '\n'), não guarda na lista de linhas
                    //Elimina '\n' do fim da string
                    for(i=strlen(ptrLinha->linha); i>=0; i--){
                        if(ptrLinha->linha[i]=='\n'){
                            ptrLinha->linha[i]='\0';
                            break;
                        }
                    }

                    InserFim(&linha, ptrLinha);


                    for(i = 0; i < strlen(ptrLinha->linha); i++){
                        if(( ptrLinha->linha[i]  >= 'A' && ptrLinha->linha[i]  <= 'Z') || ( ptrLinha->linha[i]  >= 'a' && ptrLinha->linha[i] <= 'z')){
                                for(k = 0; k < MAX_WORD; k++){
                                    if((ptrLinha->linha[i+k] >= 'A' && ptrLinha->linha[i+k] <= 'Z') || ( ptrLinha->linha[i+k] >= 'a' && ptrLinha->linha[i+k] <= 'z') || ptrLinha->linha[i+k] == '-' || ptrLinha->linha[i+k] == 39){
                                        palavra_tmp[k] = ptrLinha->linha[i+k];
                                    } else {
                                        palavra_tmp[k]='\0';
                                        break;
                                    }
                                }

                                letraMinusculas(palavra_tmp);
                                //trlwr(palavra_tmp);
                                i += k;

                                ptrpalavra = (PPALAVRA) malloc (sizeof(PALAVRA));
                                ptrpalavra2 = pesquisa(palavra, cmpPalavra, palavra_tmp);

                                if(ptrpalavra2){
                                        ptrpalavra2->ocorrencia++;
                                } else {
                                    for(k = 0; k <= strlen(palavra_tmp); k++){
                                        ptrpalavra->palavra[k] = palavra_tmp[k];
                                    }
                                    ptrpalavra->ocorrencia = 1;
                                    InserFim(&palavra, ptrpalavra);
                                }

                        }
                    }
            }
            ptrLinha = (PLINHA)malloc(sizeof(LINHA));
        }
        fclose(file);
    }

    printf("\nSucesso ao ler o ficheiro %s\n", fileName);
    printf("\nPressione ENTER para continuar...");
    getchar();

    do{
        system("cls");
        printf("\n*** Menu Principal ***\n");
        printf("\n1 - Linhas");
        printf("\n2 - Palavras Individuais");
        printf("\n3 - Lista de Significados");
        printf("\n4 - Tabelas de frequencias");
        printf("\n5 - Informacoes");
        printf("\n0 - Sair");
        printf("\n\nInsira a opcao: ");
        opcao1 = getchar();
        scanf("%*[^\n]"); scanf("%*c");
        switch(opcao1){
            case '1':
                do {
                    system("cls");
                    printf("\n*** Linhas ***\n");
                    printf("\n1 - Imprimir Sequencialmente (uma a uma)");
                    printf("\n2 - Imprimir Todas");
                    printf("\n0 - Voltar ao menu anterior");
                    printf("\n\nInsira a opcao: ");
                    opcao2 = getchar();
                    scanf("%*[^\n]"); scanf("%*c");
                    switch (opcao2){
                        case '1':
                            system("cls");
                            printf("\n*** Imprimir Sequencialmente ***\n");
                            Imprime(linha, imprimeVezLinha);
                            break;
                        case '2':
                            system("cls");
                            printf("\n*** Imprimir Todas ***\n");
                            Imprime(linha, imprimeTodaLinha);
                            break;
                        case '0':
                            opcao2 = -1;
                            break;
                    }
                }while (opcao2 != -1);
                break;
            case '2':
                do {
                    system("cls");
                    printf("\n*** Palavras Individuais ***\n");
                    printf("\n1 - Imprimir");
                    printf("\n2 - Pesquisa");
                    printf("\n0 - Voltar ao menu anterior");
                    printf("\n\nInsira a opcao: ");
                    opcao2 = getchar();
                    scanf("%*[^\n]"); scanf("%*c");
                    switch (opcao2){
                        case '1':
                            system("cls");
                            printf("\n*** Imprimir ***\n");
                            printf("\nOcorrencias - Palavra\n\n");
                            Imprime(palavra, imprimePalavras);
                            break;
                        case '2':
                            system("cls");
                            printf("\n*** Pesquisa ***");
                            printf("\n\nEscreva a palavra procurar: ");
                            fgets( palavra_tmp, MAX_WORD, stdin);
                            letraMinusculas(palavra_tmp);
                            //strlwr(palavra_tmp);
                            palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                            ptrpalavra = pesquisa(palavra, cmpPalavra, palavra_tmp);
                            if(ptrpalavra){
                                if(ptrpalavra->ocorrencia == 1){
                                    printf("\nA palavra %s ocorre %d vez no ficheiro", ptrpalavra->palavra, ptrpalavra->ocorrencia);
                                } else {
                                    printf("\nA palavra %s ocorre %d vezes no ficheiro", ptrpalavra->palavra, ptrpalavra->ocorrencia);
                                }
                            } else {
                                printf("\nA palavra %s nao existe no ficheiro", palavra_tmp);
                            }
                            getchar();
                            break;
                        case '0':
                            opcao2 = -1;
                            break;
                    }
                }while (opcao2 != -1);
                break;
            case '3':
                do {
                    system("cls");
                    printf("\n*** Lista de Significados ***\n");
                    printf("\n1 - Imprimir Significados");
                    printf("\n2 - Imprimir Palavras");
                    printf("\n3 - Adicionar Significado");
                    printf("\n4 - Remover Significado");
                    printf("\n5 - Adicionar Palavra");
                    printf("\n6 - Remover Palavra");
                    printf("\n0 - Voltar ao menu anterior");
                    printf("\n\nInsira a opcao: ");
                    opcao2 = getchar();
                    scanf("%*[^\n]"); scanf("%*c");
                    switch (opcao2){
                        case '1':
                            system("cls");
                            printf("\n*** Imprimir Significados ***\n");
                            if(significados == NULL){
                                printf("\nNao existe Significados...");
                                getchar();
                                break;
                            }
                            Imprime(significados, imprimeSignificados);
                            break;
                        case '2':
                            system("cls");
                            printf("\n*** Imprimir Palavras ***\n");
                            if(significados == NULL){
                                printf("\nNao existe Significados...");
                                getchar();
                                break;
                            }
                            printf("\nEscreva o Significado: ");
                            fgets( palavra_tmp, MAX_WORD, stdin);
                            letraMinusculas(palavra_tmp);
                            //strlwr(palavra_tmp);
                            palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                            ptrSignifica = pesquisa(significados, cmpSignificado, palavra_tmp);
                            if(ptrSignifica){
                                if(ptrSignifica->posicao == 0){
                                    printf("\nNao existe Palavras...");
                                    getchar();
                                    break;
                                }
                                printf("\nPalavras:\n\n");
                                imprimeSPalavra(ptrSignifica, imprimeSPalavra2);
                            } else {
                                printf("\nO Significado %s nao existe", palavra_tmp);
                            }
                            getchar();
                            break;
                        case '3':
                            system("cls");
                            printf("\n*** Adicionar Significado ***\n");
                            ptrSignifica = criaSignificados();
                            ptrSignifica2 = pesquisa(significados, cmpSignificado, ptrSignifica->significado);
                            if(ptrSignifica2){
                                printf("\nO Significado %s ja existe", ptrSignifica->significado);
                            } else {
                                InserFim(&significados, ptrSignifica);
                                printf("\nO Significado %s foi criado com sucesso", ptrSignifica->significado);
                            }
                            getchar();
                            break;
                        case '4':
                            system("cls");
                            printf("\n*** Remover Significado ***\n");
                            if(significados == NULL){
                                printf("\nNao existe Significados...");
                                getchar();
                                break;
                            }
                            printf("\nEscreva o Significado a remover: ");
                            fgets( palavra_tmp, MAX_WORD, stdin);
                            letraMinusculas(palavra_tmp);
                            //strlwr(palavra_tmp);
                            palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                            k = Remover(&significados, cmpSignificado, palavra_tmp);
                            if(k){
                                printf("\nSignificado %s removido", palavra_tmp);
                            } else {
                                printf("\nO Significado %s nao existe", palavra_tmp);
                            }
                            getchar();
                            break;
                        case '5':
                            system("cls");
                            printf("\n*** Adicionar Palavra ***\n");
                            if(significados == NULL){
                                printf("\nNao existe Significados...");
                                getchar();
                                break;
                            }
                            printf("\nEscreva o Significado: ");
                            fgets( palavra_tmp, MAX_WORD, stdin);
                            letraMinusculas(palavra_tmp);
                            //strlwr(palavra_tmp);
                            palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                            ptrSignifica = pesquisa(significados, cmpSignificado, palavra_tmp);
                            if(ptrSignifica){
                                ptrSPalavra = criaSPalavra();
                                ptrSPalavra2 = pesquisaSPalavra(ptrSignifica, cmpSPalavra, ptrSPalavra->spalavra);
                                if(ptrSPalavra2){
                                    printf("\nA Palavra %s ja existe", ptrSPalavra->spalavra);
                                } else {
                                    insereSPalavra(ptrSignifica, ptrSPalavra);
                                    printf("\nA Palavra %s foi criado com sucesso", ptrSPalavra->spalavra);
                                }
                            } else {
                                printf("\nO Significado %s nao existe", palavra_tmp);
                            }
                            getchar();
                            break;
                        case '6':
                            system("cls");
                            printf("\n*** Remover Palavra ***\n");
                            if(significados == NULL){
                                printf("\nNao existe Significados...");
                                getchar();
                                break;
                            }
                            printf("\nEscreva o Significado: ");
                            fgets( palavra_tmp, MAX_WORD, stdin);
                            letraMinusculas(palavra_tmp);
                            //strlwr(palavra_tmp);
                            palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                            ptrSignifica = pesquisa(significados, cmpSignificado, palavra_tmp);
                            if(ptrSignifica){
                                if(ptrSignifica->posicao == 0){
                                    printf("\nNao existe Palavras...");
                                    getchar();
                                    break;
                                }
                                printf("\n\nEscreva a Palavra: ");
                                fgets( palavra_tmp, MAX_WORD, stdin);
                                letraMinusculas(palavra_tmp);
                                //strlwr(palavra_tmp);
                                palavra_tmp[strlen(palavra_tmp) - 1] = '\0';
                                k = removerSPalavra(ptrSignifica, cmpSPalavra, palavra_tmp);
                                if(k){
                                    printf("\nA Palavra %s foi removido com sucesso", palavra_tmp);
                                } else {
                                    printf("\nA Palavra %s não existe", palavra_tmp);
                                }
                            } else {
                                printf("\nO Significado %s nao existe", palavra_tmp);
                            }
                            getchar();
                            break;
                        case '0':
                            opcao2 = -1;
                            break;
                    }
                }while (opcao2 != -1);
                break;
            case '4':
                //--------------------------falta acresentar case todo
                system("cls");
                PNO tabela = NULL; //--------------------------------------falta acresentar
                PTABELA ptrTabela; //--------------------------------------falta acresentar

                int i, Ntotal = 0, total;
                float relativa;

                for(ptr = significados; ptr; ptr=ptr->prox){
                    ptrTabela = criaTabela(palavra, ptr->dados);
                    InserFim(&tabela,ptrTabela);
                }
                total = imprimeTabela(tabela,palavra);
                printf("\n\nPalavras que ficam fora da classificacao:\n");
                printf("\n Palavra\n");
                for(ptr = palavra; ptr; ptr=ptr->prox){
                        i = imprimeFora(ptr->dados, significados);
                        Ntotal += i;
                }
                printf("\n  F.Absoluta: %d", Ntotal);
                relativa = (float) Ntotal*100/total;
                printf("\n  F.Relativa: %0.2f \%\n", relativa);
                getchar();
                break;
            case '5':
                system("cls");
                printf("\nTrabalho realizado por:\n\n");
                printf("Bruno Antunes - 21403819\n");
                printf("Nuno Nelas - 21401549\n");
                printf("Miguel Soeiro - 21401797\n");
                getchar();
                break;
            case '0':
                opcao1 = -1;
                break;
        }
    } while (opcao1 != -1);

system("cls");
printf("\n   Fim do Programa, Obrigado");
getchar();
return 0;
}


