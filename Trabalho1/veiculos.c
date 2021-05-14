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

int nomes_arqs_veiculos(FILE *arq, FILE *nv_arq, char **nm_arq, char **nm_nv_arq){    //Pra receber o nome do arq original e do novo(binario)
    *nm_arq = (char *) malloc(14 * sizeof(char));
    *nm_nv_arq = (char *) malloc(14 * sizeof(char));
    scanf("%s %s", *nm_arq, *nm_nv_arq);

    arq = fopen(*nm_arq, "r+");
    if(arq == NULL){                                        //Checa se n tem inconsistencia
        printf("Falha no processamento do arquivo.\n");
        libera_nomes_arquivos(*nm_arq, *nm_nv_arq);
        return -1;
    }fclose(arq);

    return 0;
}

void ler_cabecalho_veiculos_csv(Cb_vcl *cab, FILE *arq){                    //Pra ler cabecalho do csv
    cab->status = '0';
    cab->byteProxReg = 175;
    cab->nroRegistros = 0;
    cab->nroRegRemovidos = 0;
    fscanf(arq, "%[^,],", cab->descrevePrefixo);
    fscanf(arq, "%[^,]", cab->descreveData);
    fscanf(arq, ",%[^,]", cab->descreveLugares);
    fscanf(arq, ",%[^,]", cab->descreveLinha);
    fscanf(arq, ",%[^,]", cab->descreveModelo);
    fscanf(arq, ",%[^\n]", cab->descreveCategoria);
}

void escreve_cabecalho_bin(Cb_vcl *cab, FILE *b_arq){                       //Pra colocar o cabecalho no bin -> vai reescrever varias vezes
    fwrite(&cab->status, 1, 1, b_arq);
    fwrite(&cab->byteProxReg, 8, 1, b_arq);
    fwrite(&cab->nroRegistros, 4, 1, b_arq);
    fwrite(&cab->nroRegRemovidos, 4, 1, b_arq);
    fwrite(cab->descrevePrefixo, 1, 18, b_arq);
    fwrite(cab->descreveData, 1, 35, b_arq);
    fwrite(cab->descreveLugares, 1, 42, b_arq);
    fwrite(cab->descreveLinha, 1, 26, b_arq);
    fwrite(cab->descreveModelo, 1, 17, b_arq);
    fwrite(cab->descreveCategoria, 1, 20, b_arq);
}

void recebe_registro_csv(Dd_vcl *reg, FILE *arq){                           //Pra receber linha do csv
    char qtde_lugares[4], codline[4];

    fscanf(arq, "%[^,]", reg->prefixo);
    fscanf(arq, ",%[^,]", reg->data);
    fscanf(arq, ",%[^,]", qtde_lugares);
    fscanf(arq, ",%[^,]", codline);
    fscanf(arq, ",%[^,]", reg->modelo);
    fscanf(arq, ",%[^\n]", reg->categoria);

    if(reg->prefixo[0] == '*')  reg->removido = '0';
    else    reg->removido = '1';
    if(checa_nulo(qtde_lugares) < 0)    reg->quantidadeLugares = -1;
    else    reg->quantidadeLugares = atoi(qtde_lugares);
    if(checa_nulo(codline) < 0)    reg->codLinha = -1;
    else    reg->codLinha = atoi(codline);

    if(checa_nulo(reg->modelo) < 0)     preenche_string_nula(reg->modelo, 1);
    if(checa_nulo(reg->categoria) < 0)  preenche_string_nula(reg->categoria, 1);
    reg->tamanhoCategoria = strlen(reg->categoria);
    reg->tamanhoModelo = strlen(reg->modelo);
    reg->tamanhoRegistro = strlen(reg->categoria) + strlen(reg->modelo) + 36;   //O tamanho das strings variaveis + os fixos
}

void manipula_campos(Cb_vcl *cab, Dd_vcl *reg){                                 //Pra manipular os campos nulos e mudar o cabeçalho
    if(checa_nulo(reg->prefixo) < 0)    preenche_string_nula(reg->prefixo, 5);
    if(checa_nulo(reg->data) < 0)       preenche_string_nula(reg->data, 10);

    if(reg->removido == '0'){
        cab->nroRegRemovidos++;
        for(int i = 0; i < 4; i++)
            reg->prefixo[i] = reg->prefixo[i + 1];
        reg->prefixo[4] = '\0';
    }else    
        cab->nroRegistros++;
}

void preenche_dados_bin(Dd_vcl *reg, FILE *b_arq){                              //Pra preencher 1 "linha" do bin
    fwrite(&reg->removido, 1, 1, b_arq);
    fwrite(&reg->tamanhoRegistro, 4, 1, b_arq);
    fwrite(reg->prefixo, 1, 5, b_arq);
    fwrite(reg->data, 1, 10, b_arq);
    fwrite(&reg->quantidadeLugares, 4, 1, b_arq);
    fwrite(&reg->codLinha, 4, 1, b_arq);
    fwrite(&reg->tamanhoModelo, 4, 1, b_arq);
    if(reg->modelo[0] != '\0')      fwrite(reg->modelo, 1, strlen(reg->modelo), b_arq);
    fwrite(&reg->tamanhoCategoria, 4, 1, b_arq);
    if(reg->categoria[0] != '\0')   fwrite(reg->categoria, 1, strlen(reg->categoria), b_arq);
}

void ler_cabecalho_veiculos_bin(Cb_vcl *cab, FILE *b_arq){    //Ler o cabecalho direto do bin
    fread(&cab->status, 1, 1, b_arq);
    fread(&cab->byteProxReg, 8, 1, b_arq);
    fread(&cab->nroRegistros, 4, 1, b_arq);
    fread(&cab->nroRegRemovidos, 4, 1, b_arq);
    fread(cab->descrevePrefixo, 18, 1, b_arq);
    fread(cab->descreveData, 35, 1, b_arq);
    fread(cab->descreveLugares, 42, 1, b_arq);
    fread(cab->descreveLinha, 26, 1, b_arq);
    fread(cab->descreveModelo, 17, 1, b_arq);
    fread(cab->descreveCategoria, 20, 1, b_arq);
}

void recebe_registro_bin(Dd_vcl *reg, FILE *b_arq){
    fread(&reg->removido, 1, 1, b_arq);
    fread(&reg->tamanhoRegistro, 4, 1, b_arq);
    fread(reg->prefixo, 5, 1, b_arq);
    fread(reg->data, 10, 1, b_arq);
    fread(&reg->quantidadeLugares, 4, 1, b_arq);
    fread(&reg->codLinha, 4, 1, b_arq);
    fread(&reg->tamanhoModelo, 4, 1, b_arq);
    if(reg->tamanhoModelo > 0)
        fread(reg->modelo, reg->tamanhoModelo, 1, b_arq);
    fread(&reg->tamanhoCategoria, 4, 1, b_arq);
    if(reg->tamanhoCategoria > 0)
        fread(reg->categoria, reg->tamanhoCategoria, 1, b_arq);
}

void imprime_registro(Cb_vcl *cab,Dd_vcl *reg){
    char *cab1 = trata_string(cab->descrevePrefixo, 5);
    char *cab2 = trata_string(cab->descreveModelo, 17);
    char *cab3 = trata_string(cab->descreveCategoria, 20);
    char *cab4 = trata_string(cab->descreveData, 35);
    char *cab5 = trata_string(cab->descreveLugares, 42);
    char *reg1 = trata_string(reg->prefixo, 5);
    char *reg2 = trata_string(reg->modelo, reg->tamanhoModelo);
    char *reg3 = trata_string(reg->categoria, reg->tamanhoCategoria);
    char *reg4 = trata_string(reg->data, 10);

    printf("%s: %s\n", cab1, reg1);
    printf("%s: %s\n", cab2, reg2);
    printf("%s: %s\n", cab3, reg3);
    printf("%s: %s\n", cab4, reg4);
    if(reg->quantidadeLugares != -1)
        printf("%s: %d\n\n", cab5, reg->quantidadeLugares);
    else
        printf("%s: campo com valor nulo\n\n", cab5);
    free(cab1);
    free(cab2);
    free(cab3);
    free(cab4);
    free(cab5);
    free(reg1);
    free(reg2);
    free(reg3);
    free(reg4);
}