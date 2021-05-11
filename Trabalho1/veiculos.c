/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo .c contém funções relacionadas ao arquivo de veiculos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h"
#include "gerais.h"

void carrega_veiculos(){
    FILE *arq, *nv_arq;
    char *nm_arq, *nm_nv_arq;
    if(nomes_arqs_veiculos(arq, nv_arq, nm_arq, nm_nv_arq) < 0)
        return;

    //Foi aconselhado n usar muito a RAM -> Ler registro e logo colocar no binário, sem vetores



    fecha_arquivos(arq, nv_arq);
    binarioNaTela(nm_nv_arq);
    libera_nomes_arquivos(nm_arq, nm_nv_arq);
}

int nomes_arqs_veiculos(FILE *arq, FILE *nv_arq, char *nm_arq, char *nm_nv_arq){
    FILE *p_arq = NULL, *p_nv_arq = NULL;
    char *nm_arq = (char *) malloc(11 * sizeof(char));
    char *nm_nv_arq = (char *) malloc(11 * sizeof(char));
    scanf("%s %s",nm_arq, nm_nv_arq);

    p_arq = fopen(nm_arq, "r+");
    if(checa_status(p_arq) < 0){
        printf("Falha no processamento do arquivo.\n");
        libera_nomes_arquivos(nm_arq, nm_nv_arq);
        return -1;
    }
    nv_arq = fopen(nm_nv_arq, "wb+");

    return 0;
}

void dados_veiculos(){
    Cb_vcl cabecalho;
    Dd_vcl dados;
    char campo_nulo[] = "campo com valor nulo";
    char *nm_arq = (char *) malloc(11 * sizeof(char));
    scanf("%s", nm_arq);

    FILE *arq = fopen(nm_arq, "rb+");
    if(checa_status(arq) < 0){
        free(nm_arq);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    ler_cabecalho_veiculos(&cabecalho, arq);
    if(cabecalho.nroRegistros <= 0){
        printf("Registro inexistente.\n");
        fclose(arq);
        free(nm_arq);
        return;
    }

    do{
        printf("");
    }while(1);

    fclose(arq);
    free(nm_arq);
}

void ler_cabecalho_veiculos(Cb_vcl *cabecalho, FILE *arq){
    fread(cabecalho->status, 1, 1, arq);
    fread(cabecalho->byteProxReg, 8, 1, arq);
    fread(cabecalho->nroRegistros, 4, 1, arq);
    fread(cabecalho->nroRegRemovidos, 4, 1, arq);
    fread(cabecalho->descrevePrefixo, 18, 1, arq);
    fread(cabecalho->descreveData, 35, 1, arq);
    fread(cabecalho->descreveLugares, 42, 1, arq);
    fread(cabecalho->descreveLinha, 26, 1, arq);
    fread(cabecalho->descreveModelo, 17, 1, arq);
    fread(cabecalho->descreveCategoria, 20, 1, arq);
}