/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções relacionadas
    ao arquivo de veiculos assim como a estrutura de seu registro
*/
#ifndef __VEICULOS_H__
#define __VEICULOS_H__

typedef struct cabecalho_veiculos{      //Elementos que compõem o registro de cabeçalho do arquivo de veiculos
    char status;
    long long int byteProxReg;
    int nroRegistros;
    int nroRegRemovidos;
    char descrevePrefixo[18];
    char descreveData[35];
    char descreveLugares[42];
    char descreveLinha[26];
    char descreveModelo[17];
    char descreveCategoria[20];
}Cb_vcl;

typedef struct dados_veiculos{          //Elementos que compõem o registro de dados do arquivo de veiculos
    char prefixo[5];
    char data[10];
    int quantidadeLugares;
    int codLinha;
    char *modelo;
    char *categoria;
    char removido;
    int tamanhoRegistro;                //Tamanho registro conta tudo menos o "removido" e ele msm, prefixo ->
    int tamanhoModelo;
    int tamanhoCategoria;
}Dd_vcl;
                        //Abaixo temos o cabeçalho das funções do "veiculos.h"
void carrega_veiculos();
int nomes_arqs_veiculos(FILE *arq, FILE *nv_arq, char *nm_arq, char *nm_nv_arq);




#endif /* __VEICULOS_H__ */