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

int nomes_arqs_veiculos(FILE **arq, FILE *nv_arq, char **nm_arq, char **nm_nv_arq){    //Pra receber o nome do arq original e do novo(binario)
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

void ler_cabecalho_csv_veiculos(Cb_vcl *cab, FILE *arq){                    //Pra ler cabecalho do csv
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
    getc(arq);
}

void escreve_cabecalho_bin_veiculos(Cb_vcl *cab, FILE *b_arq){                       //Pra colocar o cabecalho no bin -> vai reescrever varias vezes
    fwrite(cab, sizeof(Cb_vcl), 1, b_arq);
}

void recebe_registro_csv_veiculos(Dd_vcl *reg, FILE *arq){                           //Pra receber linha do csv
    char qtde_lugares[4], codline[4];

    fscanf(arq, "%[^,]", reg->prefixo);
    fscanf(arq, ",%[^,]", reg->data);
    fscanf(arq, ",%[^,]", qtde_lugares);
    fscanf(arq, ",%[^,]", codline);
    fscanf(arq, ",%[^,]", reg->modelo);
    fscanf(arq, ",%[^\n]", reg->categoria);
    getc(arq);

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
    reg->tamanhoRegistro = strlen(reg->categoria) + strlen(reg->modelo) + 31;   //O tamanho das strings variaveis + os fixos
}

void manipula_campos_veiculos(Cb_vcl *cab, Dd_vcl *reg){                                 //Pra manipular os campos nulos e mudar o cabeçalho
    if(checa_nulo(reg->prefixo) < 0)    preenche_string_nula(reg->prefixo, 5);
    else if(strlen(reg->prefixo) != 5)  preenche_lixo(reg->prefixo, strlen(reg->prefixo), 5);
    if(checa_nulo(reg->data) < 0)       preenche_string_nula(reg->data, 10);
    else if(strlen(reg->data) != 10)    preenche_lixo(reg->data, strlen(reg->data), 10);

    if(reg->removido == '0'){
        cab->nroRegRemovidos++;
        for(int i = 0; i < 4; i++)
            reg->prefixo[i] = reg->prefixo[i + 1];
        reg->prefixo[4] = '\0';
    }else    
        cab->nroRegistros++;
}

void preenche_dados_bin_veiculos(Dd_vcl *reg, FILE *b_arq){                              //Pra preencher 1 "linha" do bin
    fwrite(&reg->removido, 1, 1, b_arq);
    fwrite(&reg->tamanhoRegistro, 4, 1, b_arq);
    fwrite(reg->prefixo, 1, 5, b_arq);
    fwrite(reg->data, 1, 10, b_arq);
    fwrite(&reg->quantidadeLugares, 4, 1, b_arq);
    fwrite(&reg->codLinha, 4, 1, b_arq);
    fwrite(&reg->tamanhoModelo, 4, 1, b_arq);
    if(reg->tamanhoModelo > 0)      fwrite(reg->modelo, 1, reg->tamanhoModelo, b_arq);
    fwrite(&reg->tamanhoCategoria, 4, 1, b_arq);
    if(reg->tamanhoCategoria > 0)   fwrite(reg->categoria, 1, reg->tamanhoCategoria, b_arq);
}

void ler_cabecalho_bin_veiculos(Cb_vcl *cabecalho, FILE *b_arq){                  //Essa função irá ler o cabeçalho do arquivo binário de veículos
    fread(&cabecalho->status, 1, 1, b_arq);                                       //A leitura de cada item foi feita utilizando "fread" e os tamanhos
    fread(&cabecalho->byteProxReg, 8, 1, b_arq);                                  //das variáveis de acordo com a descrição do trabalho
    fread(&cabecalho->nroRegistros, 4, 1, b_arq);
    fread(&cabecalho->nroRegRemovidos, 4, 1, b_arq);
    fread(cabecalho->descrevePrefixo, 18, 1, b_arq);
    fread(cabecalho->descreveData, 35, 1, b_arq);
    fread(cabecalho->descreveLugares, 42, 1, b_arq);
    fread(cabecalho->descreveLinha, 26, 1, b_arq);
    fread(cabecalho->descreveModelo, 17, 1, b_arq);
    fread(cabecalho->descreveCategoria, 20, 1, b_arq);
}

void recebe_registro_bin_veiculos(Dd_vcl *reg, FILE *b_arq){                         //Essa função irá ler 1 registro do arquivo binário de veículos
    fread(&reg->removido, 1, 1, b_arq);                                     //A leitura de cada item foi feita utilizando "fread" e os tamanhos,
    fread(&reg->tamanhoRegistro, 4, 1, b_arq);                              //das variáveis fixas, obtido de acordo com a descrição do trabalho
    fread(reg->prefixo, 1, 5, b_arq);
    fread(reg->data, 1, 10, b_arq);
    fread(&reg->quantidadeLugares, 4, 1, b_arq);
    fread(&reg->codLinha, 4, 1, b_arq);
    fread(&reg->tamanhoModelo, 4, 1, b_arq);
    if(reg->tamanhoModelo > 0)
        fread(reg->modelo, 1, reg->tamanhoModelo, b_arq);
    fread(&reg->tamanhoCategoria, 4, 1, b_arq);
    if(reg->tamanhoCategoria > 0)
        fread(reg->categoria, 1, reg->tamanhoCategoria, b_arq);
}

void imprime_registro_veiculos(Cb_vcl *cab, Dd_vcl *reg){                             //Essa função irá utilizar o cabeçalho do arquivo (cab) e o atual
    char *cab1 = trata_string(cab->descrevePrefixo, 18);                    //registro analisado (reg) para imprimir corretamente as informações
    char *cab2 = trata_string(cab->descreveModelo, 17);                     //Cada string imprimível será obtida com o retorno da função "trata_string",
    char *cab3 = trata_string(cab->descreveCategoria, 20);                  //declarada no arquivo "gerais.c"
    char *cab4 = trata_string(cab->descreveData, 35);
    char *cab5 = trata_string(cab->descreveLugares, 42);
    char *reg1 = trata_string(reg->prefixo, 5);
    char *reg2 = trata_string(reg->modelo, reg->tamanhoModelo);
    char *reg3 = trata_string(reg->categoria, reg->tamanhoCategoria);
    char *reg4 = trata_string(reg->data, 10);

    printf("%s: %s\n", cab1, reg1);                                         //Uma vez obtidas, basta imprimir as strings e depois liberarmos o espaço
    printf("%s: %s\n", cab2, reg2);                                         //utilizado por cada uma
    printf("%s: %s\n", cab3, reg3);
    printf("%s: %s\n", cab4, reg4);
    if(reg->quantidadeLugares != -1)    printf("%s: %d\n\n", cab5, reg->quantidadeLugares);
    else    printf("%s: campo com valor nulo\n\n", cab5);
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

int checa_impressao_veiculos(char *busca, char *campo, Dd_vcl *reg){                 //Essa função irá verificar se o registro (reg) recebido possui
    int verifica = -1;                                                      //o valor "busca" em seu "campo", ou seja, se esse registro
    char *aux = NULL;                                                       //poderá ou não ser impresso

    if(strcmp(campo, "prefixo") == 0){                                      //Com os ifs e else-ifs externos, saberemos em qual campo do registro
        aux = trata_string(reg->prefixo, 5);                                //devemos procurar. Depois, usaremos "trata_string" para manipular o
        if(strcmp(busca, aux) == 0) verifica++;                             //valor do campo e compará-lo com "busca"
    }else if(strcmp(campo, "data") == 0){
        aux = trata_string(reg->data, 10);
        if(strcmp(busca, aux) == 0) verifica++;
    }else if(strcmp(campo, "quantidadeLugares") == 0){                      //Usaremos "atoi" para comparar o valor de "quantidadeLugares"
        if(strcmp(busca, "NULO") == 0 && reg->quantidadeLugares == -1)  verifica++;
        else if(atoi(busca) == reg->quantidadeLugares)  verifica++;
    }else if(strcmp(campo, "modelo") == 0){                                 //Para campos de tamanhos variáveis, verificaremos seus tamanhos e as
        if(strcmp(busca, "NULO") == 0 && reg->tamanhoModelo == -1)  verifica++; //strings, caso não sejam nulas
        aux = trata_string(reg->modelo, reg->tamanhoModelo);
        if(strcmp(busca, aux) == 0) verifica++;
    }else if(strcmp(campo, "categoria") == 0){
        if(strcmp(busca, "NULO") == 0 && reg->tamanhoCategoria == -1)   verifica++;
        aux = trata_string(reg->categoria, reg->tamanhoCategoria);
        if(strcmp(busca, aux) == 0) verifica++;
    }
    free(aux);
    return verifica;                                                        //Retornaremos -1 se não devemos imprimir e 0 caso seja necessário
}

void recebe_registro_ep_veiculos(Dd_vcl *reg){                                       //Função que irá receber as informações de um novo registro a partir
    char aux_lugares[4], aux_cod[6];                                        //da entrada padrão
    reg->removido = '1';                                                    //Primeiramente, sinalizaremos que o registro não é um dos removidos

    scan_quote_string(reg->prefixo);                                        //Depois, usaremos "scan_quote_string" para receber os valores dos campos
    getchar();
    scan_quote_string(reg->data);
    getchar();
    scan_quote_string(aux_lugares);
    getchar();
    scan_quote_string(aux_cod);
    scan_quote_string(reg->modelo);
    scan_quote_string(reg->categoria);

    if(checa_nulo(reg->prefixo) < 0)    preenche_string_nula(reg->prefixo, 5);                  //Então, essa sequência de ifs e else-ifs verificará
    else if(strlen(reg->prefixo) != 5)  preenche_lixo(reg->prefixo, strlen(reg->prefixo), 5);   //se as strings são nulas com "checa_nulo". Caso forem,
    if(checa_nulo(reg->data) < 0)       preenche_string_nula(reg->data, 10);                    //usaremos "preenche_string_nula" para preenche-las
    else if(strlen(reg->data) != 10)    preenche_lixo(reg->data, strlen(reg->data), 10);        //Caso não sejam, verificaremos se há lixo nelas e
    if(checa_nulo(aux_lugares) < 0)     reg->quantidadeLugares = -1;                            //trataremos com "preenche_lixo"
    else    reg->quantidadeLugares = atoi(aux_lugares);                                         //Se as strings referentes aos inteiros não forem nulas,
    if(checa_nulo(aux_cod) < 0)         reg->codLinha = -1;                                     //obteremos seu valor com "atoi"
    else    reg->codLinha = atoi(aux_cod);
    if(checa_nulo(reg->modelo) < 0){                                        //Durante a checagem das strings de "modelo" e "categoria", também atribuiremos
        reg->tamanhoModelo = 0;                                             //o valor de "tamanhoModelo" e "tamanhoCategoria"
        preenche_string_nula(reg->modelo, 1);
    }else   reg->tamanhoModelo = strlen(reg->modelo);
    if(checa_nulo(reg->categoria) < 0){
        reg->tamanhoCategoria = 0;
        preenche_string_nula(reg->categoria, 1);
    }else   reg->tamanhoCategoria = strlen(reg->categoria);
    reg->tamanhoRegistro = 31 + reg->tamanhoModelo + reg->tamanhoCategoria;//Por fim, obteremos o tamanho total desse registro
}