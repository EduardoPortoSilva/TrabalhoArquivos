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
    Cb_vcl cabecalho;
    Dd_vcl registro;
    FILE *arq, *nv_arq;
    char *nm_arq, *nm_nv_arq;
    if(nomes_arqs_veiculos(arq, nv_arq, nm_arq, nm_nv_arq) < 0)
        return;

    ler_cabecalho_veiculos_csv(&cabecalho, arq);
    escreve_cabecalho_bin(&cabecalho, nv_arq);
    while(cabecalho.nroRegistros != 0 && !feof(arq)){       //Mudar essa condição se pah -> Usar ftell e fseek constantemente!!
        recebe_registro_csv(&registro, arq);
        manipula_campos(&cabecalho, &registro);
        preenche_dados_bin(&registro, nv_arq);
    }
    fecha_arquivos(arq, nv_arq);                            //Fechar os arqs pra poder chamar a função do monitor
    binarioNaTela(nm_nv_arq);
    libera_nomes_arquivos(nm_arq, nm_nv_arq);
}

int nomes_arqs_veiculos(FILE *arq, FILE *nv_arq, char *nm_arq, char *nm_nv_arq){    //Pra receber o nome do arq original e do novo(binario)
    FILE *p_arq = NULL, *p_nv_arq = NULL;
    char *nm_arq = (char *) malloc(11 * sizeof(char));
    char *nm_nv_arq = (char *) malloc(11 * sizeof(char));
    scanf("%s %s",nm_arq, nm_nv_arq);

    p_arq = fopen(nm_arq, "r+");
    if(checa_status(p_arq) < 0){                                        //Checa se n tem inconsistencia
        printf("Falha no processamento do arquivo.\n");
        libera_nomes_arquivos(nm_arq, nm_nv_arq);
        return -1;
    }
    nv_arq = fopen(nm_nv_arq, "wb+");

    return 0;
}

void ler_cabecalho_veiculos_csv(Cb_vcl *cab, FILE *arq){                    //Pra ler cabecalho do csv
    cab->status = 0;
    cab->byteProxReg = 0;
    cab->nroRegistros = 0;
    cab->nroRegRemovidos = 0;
    fscanf(arq, "%[^,]", cab->descrevePrefixo);
    fscanf(arq, "%[^,]", cab->descreveData);
    fscanf(arq, "%[^,]", cab->descreveLugares);
    fscanf(arq, "%[^,]", cab->descreveLinha);
    fscanf(arq, "%[^,]", cab->descreveModelo);
    fscanf(arq, "%[^,]", cab->descreveCategoria);
}

void escreve_cabecalho_bin(Cb_vcl *cab, FILE *b_arq){                       //Pra colocar o cabecalho no bin -> vai reescrever varias vezes
    fwrite(&cab->status, 1, 1, b_arq);
    fwrite(&cab->byteProxReg, 1, 8, b_arq);
    fwrite(&cab->nroRegistros, 1, sizeof(int), b_arq);
    fwrite(&cab->nroRegRemovidos, 1, sizeof(int), b_arq);
    fwrite(&cab->descrevePrefixo, 1, 18, b_arq);
    fwrite(&cab->descreveData, 1, 35, b_arq);
    fwrite(&cab->descreveLugares, 1, 42, b_arq);
    fwrite(&cab->descreveLinha, 1, 26, b_arq);
    fwrite(&cab->descreveModelo, 1, 17, b_arq);
    fwrite(&cab->descreveCategoria, 1, 20, b_arq);
}

void recebe_registro_csv(Dd_vcl *reg, FILE *arq){                           //Pra receber linha do csv
    fscanf(arq, "%[^,]", reg->prefixo);
    fscanf(arq, "%[^,]", reg->data);
    fscanf(arq, "%[^,]", reg->quantidadeLugares);
    fscanf(arq, "%[^,]", reg->codLinha);
    fscanf(arq, "%[^,]", reg->modelo);
    fscanf(arq, "%[^,]", reg->categoria);
    fscanf(arq, "%[^,]", reg->removido);
    reg->tamanhoCategoria = strlen(reg->categoria);
    reg->tamanhoModelo = strlen(reg->modelo);
    reg->tamanhoRegistro = strlen(reg->categoria) + strlen(reg->modelo) + 36; //O tamanho das strings variaveis + os 36 fixos
}

void manipula_campos(Cb_vcl *cab, Dd_vcl *reg){                         //Pra manipular os campos nulos, usar atoi e ver se ta removido
    
}

void preenche_dados_bin(Dd_vcl *reg, FILE *b_arq){                      //Pra preencher 1 "linha" do bin

}

void dados_veiculos(){
    Cb_vcl cabecalho;
    Dd_vcl dados;
    char campo_nulo[] = "campo com valor nulo";                     //Pra impressao de nulos
    char *nm_arq = (char *) malloc(11 * sizeof(char));
    scanf("%s", nm_arq);

    FILE *arq = fopen(nm_arq, "rb+");
    if(checa_status(arq) < 0){                                      //Pra ver se o arquivo n ta inconsistente
        free(nm_arq);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    ler_cabecalho_veiculos_bin(&cabecalho, arq);
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

void ler_cabecalho_veiculos_bin(Cb_vcl *cabecalho, FILE *b_arq){    //Ler o cabecalho direto do bin
    fread(cabecalho->status, 1, 1, b_arq);
    fread(cabecalho->byteProxReg, 8, 1, b_arq);
    fread(cabecalho->nroRegistros, 4, 1, b_arq);
    fread(cabecalho->nroRegRemovidos, 4, 1, b_arq);
    fread(cabecalho->descrevePrefixo, 18, 1, b_arq);
    fread(cabecalho->descreveData, 35, 1, b_arq);
    fread(cabecalho->descreveLugares, 42, 1, b_arq);
    fread(cabecalho->descreveLinha, 26, 1, b_arq);
    fread(cabecalho->descreveModelo, 17, 1, b_arq);
    fread(cabecalho->descreveCategoria, 20, 1, b_arq);
}