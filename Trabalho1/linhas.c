/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo .c contém as funções relacionadas ao arquivo de linhas
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linhas.h"
#include "gerais.h"

int nomes_arqs_linhas(FILE **arq, FILE *nv_arq, char **nm_arq, char **nm_nv_arq){    //Pra receber o nome do arq original e do novo(binario)
    *nm_arq = (char *) malloc(14 * sizeof(char));
    *nm_nv_arq = (char *) malloc(14 * sizeof(char));
    scanf("%s %s", *nm_arq, *nm_nv_arq);

    *arq = fopen(*nm_arq, "r+");
    if(*arq == NULL){                                        //Checa se n tem inconsistencia
        printf("Falha no processamento do arquivo.\n");
        free(*nm_arq);
        free(*nm_nv_arq);
        return -1;
    }

    return 0;
}

void ler_cabecalho_csv_linhas(Cb_ln *cab, FILE *arq){                    //Pra ler cabecalho do csv
    cab->status = '0';
    cab->byteProxReg = 83;
    cab->nroRegistros = 0;
    cab->nroRegRemovidos = 0;
    fscanf(arq, "%[^,],", cab->descreveCodigo);
    fscanf(arq, "%[^,]", cab->descreveCartao);
    fscanf(arq, ",%[^,]", cab->descreveNome);
    fscanf(arq, ",%[^\n]", cab->descreveCor);
    getc(arq);
}

void escreve_cabecalho_bin_linhas(Cb_ln *cab, FILE *b_arq){
    fwrite(cab, sizeof(Cb_ln), 1, b_arq);
}
void recebe_registro_csv_linhas(Dd_ln *reg, FILE *arq) {
    char tamanhoNome[4], codline[4], tamanhoCor[4], cartao;
    memset(reg->corLinha, '\0', 8);
    memset(reg->nomeLinha, '\0', 20);
    fscanf(arq, "%[^,],", codline);
    reg->aceitaCartao = getc(arq);
    fscanf(arq, ",%[^,]", reg->nomeLinha);
    fscanf(arq, ",%[^\n]", reg->corLinha);
    getc(arq);

    if (codline[0] == '*') {
        reg->removido = '0';
        if (checa_nulo(&codline[1]) < 0) reg->codLinha = -1;
        else reg->codLinha = atoi(&codline[1]);
    }else {
        reg->removido = '1';
        if (checa_nulo(codline) < 0) reg->codLinha = -1;
        else reg->codLinha = atoi(codline);
    }
    if (checa_nulo(reg->nomeLinha) < 0){
        reg->nomeLinha[0] = '\0';
        reg->tamanhoNome = 0;
    }else{
        reg->tamanhoNome = strlen(reg->nomeLinha);
    }
    if (checa_nulo(reg->corLinha) < 0){
        reg->corLinha[0] = '\0';
        reg->tamanhoCor = 0;
    }else{
        reg->tamanhoCor = strlen(reg->corLinha);
    }
    reg->tamanhoRegistro = 13 + reg->tamanhoNome + reg->tamanhoCor; //O tamanho das strings variaveis + os fixos*/
}
void manipula_campos_linhas(Cb_ln *cab, Dd_ln *reg){
    if(reg->removido == '0'){
        cab->nroRegRemovidos++;
    }else
        cab->nroRegistros++;
}
void preenche_dados_bin_linhas(Dd_ln *reg, FILE *b_arq){
    fflush(b_arq);
    fwrite(&reg->removido, 1, 1, b_arq);
    fflush(b_arq);
    fwrite(&reg->tamanhoRegistro, 4, 1, b_arq);
    fflush(b_arq);
    fwrite(&reg->codLinha, 4, 1, b_arq);
    fflush(b_arq);
    fwrite(&reg->aceitaCartao, 1, 1, b_arq);
    fflush(b_arq);
    fwrite(&reg->tamanhoNome, 1, 4, b_arq);
    fflush(b_arq);
    if(reg->tamanhoNome > 0)fwrite(reg->nomeLinha, reg->tamanhoNome, 1, b_arq);
    fflush(b_arq);
    fwrite(&reg->tamanhoCor, 1, 4, b_arq);
    fflush(b_arq);
    if(reg->tamanhoCor > 0)fwrite(reg->corLinha, reg->tamanhoCor, 1, b_arq);
    fflush(b_arq);
}

void ler_cabecalho_bin_linhas(Cb_ln *cabecalho, FILE *b_arq){
    fread(&cabecalho->status, 1, 1, b_arq);                                       //A leitura de cada item foi feita utilizando "fread" e os tamanhos
    fread(&cabecalho->byteProxReg, 8, 1, b_arq);                                  //das variáveis de acordo com a descrição do trabalho
    fread(&cabecalho->nroRegistros, 4, 1, b_arq);
    fread(&cabecalho->nroRegRemovidos, 4, 1, b_arq);
    fread(cabecalho->descreveCodigo, 15, 1, b_arq);
    fread(cabecalho->descreveCartao, 13, 1, b_arq);
    fread(cabecalho->descreveNome, 13, 1, b_arq);
    fread(cabecalho->descreveCor, 24, 1, b_arq);
}

void recebe_registro_bin_linhas(Dd_ln *reg, FILE *b_arq){
    fread(&reg->removido, 1, 1, b_arq);                                     //A leitura de cada item foi feita utilizando "fread" e os tamanhos,
    fread(&reg->tamanhoRegistro, 4, 1, b_arq);                              //das variáveis fixas, obtido de acordo com a descrição do trabalho
    fread(&reg->codLinha, 1, 4, b_arq);
    fread(&reg->aceitaCartao, 1, 1, b_arq);
    fread(&reg->tamanhoNome, 1, 4, b_arq);
    if(reg->tamanhoNome > 0)
        fread(reg->nomeLinha, 1, reg->tamanhoNome, b_arq);
    fread(&reg->tamanhoCor, 1, 4, b_arq);
    if(reg->tamanhoCor > 0)
        fread(reg->corLinha, 1, reg->tamanhoCor, b_arq);
}

char *itoa(int i){
    int size = 1;
    int j = 1;
    while(j<(i+1)){
        size++;
        j *= 10;
    }
    char *a = malloc(size);
    a[size-1] = '\0';
    for(int j = 0; j < size - 1; j ++){
        a[size-j-2] = i%10 + '0';
        i /= 10;
    }
    return a;
}

void imprime_registro_linhas(Cb_ln *cab, Dd_ln *reg){
    char *cab1 = trata_string_linhas(cab->descreveCodigo, 15);                    //registro analisado (reg) para imprimir corretamente as informações
    char *cab2 = trata_string_linhas(cab->descreveNome, 13);                     //Cada string imprimível será obtida com o retorno da função "trata_string_linhas",
    char *cab3 = trata_string_linhas(cab->descreveCor, 24);                  //declarada no arquivo "gerais.c"
    char *cab4 = trata_string_linhas(cab->descreveCartao, 13);
    char *reg1 = trata_string_linhas(itoa(reg->codLinha), 5);
    char *reg2 = trata_string_linhas(reg->nomeLinha, reg->tamanhoNome);
    char *reg3 = trata_string_linhas(reg->corLinha, reg->tamanhoCor);
    char *reg4 = trata_string_linhas(
            (reg->aceitaCartao == 'S') ? "PAGAMENTO SOMENTE COM CARTAO SEM PRESENCA DE COBRADOR" : (reg->aceitaCartao ==
                                                                                                    'N')
                                                                                                   ? "PAGAMENTO EM CARTAO E DINHEIRO"
                                                                                                   : "PAGAMENTO EM CARTAO SOMENTE NO FINAL DE SEMANA",
            (reg->aceitaCartao == 'S') ? 53 : (reg->aceitaCartao == 'N') ? 30 : 46);

    printf("%s: %s\n", cab1, reg1);                                         //Uma vez obtidas, basta imprimir as strings e depois liberarmos o espaço
    printf("%s: %s\n", cab2, reg2);                                         //utilizado por cada uma
    printf("%s: %s\n", cab3, reg3);
    printf("%s: %s\n", cab4, reg4);
    free(cab1);
    free(cab2);
    free(cab3);
    free(cab4);
    free(reg1);
    free(reg2);
    free(reg3);
    free(reg4);
    printf("\n");
}

int checa_impressao_linhas(char *busca, char *campo, Dd_ln *reg){
    int verifica = -1;
    char *aux = NULL;

    if(strcmp(campo, "codLinha") == 0){
        aux = trata_string_linhas(itoa(reg->codLinha), 4);
        if(strcmp(busca, aux) == 0) verifica++;
    }else if(strcmp(campo, "aceitaCartao") == 0){
        aux = trata_string_linhas((reg->aceitaCartao == 'S') ? "PAGAMENTO SOMENTE COM CARTAO SEM PRESENCA DE COBRADOR" : (reg->aceitaCartao == 'N')
                                                                                                                           ? "PAGAMENTO EM CARTAO E DINHEIRO"
                                                                                                                           : "PAGAMENTO EM CARTAO SOMENTE NO FINAL DE SEMANA",
                                    (reg->aceitaCartao == 'S') ? 53 : (reg->aceitaCartao == 'N') ? 30 : 46);
        if(strcmp(busca, aux) == 0) verifica++;
    }else if(strcmp(campo, "nomeLinha") == 0){
        if(strcmp(busca, "NULO") == 0 && reg->tamanhoNome == -1)  verifica++;
        aux = trata_string_veiculos(reg->nomeLinha, reg->tamanhoNome);
        if(strcmp(busca, aux) == 0) verifica++;
    }else if(strcmp(campo, "corLinha") == 0){
        if(strcmp(busca, "NULO") == 0 && reg->tamanhoCor == -1)  verifica++;
        aux = trata_string_veiculos(reg->corLinha, reg->tamanhoCor);
        if(strcmp(busca, aux) == 0) verifica++;
    }
    free(aux);
    return verifica;
}

void recebe_registro_ep_linhas(Dd_ln *reg){
    FILE *a = stdin;
    char aux_lugares[4], aux_cod[6], cartao[4];                                        //da entrada padrão
    reg->removido = '1';                                                    //Primeiramente, sinalizaremos que o registro não é um dos removidos
    scanf("%d ",&reg->codLinha);                                      //Depois, usaremos "scan_quote_string" para receber os valores dos campos
    scan_quote_string(cartao);
    reg->aceitaCartao = cartao[0];
    scan_quote_string(reg->nomeLinha);
    if(strcmp(reg->nomeLinha, "NULO") + strcmp(reg->nomeLinha, "nulo") == 0){
        reg->tamanhoNome = 0;
        reg->nomeLinha[0] = '\0';
    }else{
        reg->tamanhoNome = strlen(reg->nomeLinha);
    }
    getchar();
    scan_quote_string(reg->corLinha);
    if(strcmp(reg->corLinha, "NULO") + strcmp(reg->corLinha, "nulo") == 0){
        reg->tamanhoCor = 0;
        reg->corLinha[0] = '\0';
    } else {
        reg->tamanhoCor = strlen(reg->corLinha);
    }
    getchar();
    reg->tamanhoRegistro = 13 + reg->tamanhoNome + reg->tamanhoCor;//Por fim, obteremos o tamanho total desse registro
}
