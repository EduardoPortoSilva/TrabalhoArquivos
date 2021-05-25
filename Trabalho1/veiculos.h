/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções relacionadas
    ao arquivo de veiculos assim como a estrutura de seu registro
*/
#ifndef __VEICULOS_H__
#define __VEICULOS_H__

typedef struct __attribute__((__packed__)) cabecalho_veiculos{      //Elementos que compõem o registro de cabeçalho do arquivo de veiculos
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
    char modelo[100];
    char categoria[100];
    char removido;
    int tamanhoRegistro;
    int tamanhoModelo;
    int tamanhoCategoria;
}Dd_vcl;
                        //Abaixo temos o cabeçalho das funções do "veiculos.h"
int nomes_arqs_veiculos(FILE **arq, FILE *nv_arq, char **nm_arq, char **nm_nv_arq);
void ler_cabecalho_csv_veiculos(Cb_vcl *cab, FILE *arq);
void escreve_cabecalho_bin_veiculos(Cb_vcl *cab, FILE *b_arq);
void recebe_registro_csv_veiculos(Dd_vcl *reg, FILE *arq);
void manipula_campos_veiculos(Cb_vcl *cab, Dd_vcl *reg);
void preenche_dados_bin_veiculos(Dd_vcl *reg, FILE *b_arq);
void ler_cabecalho_bin_veiculos(Cb_vcl *cabecalho, FILE *b_arq);
void recebe_registro_bin_veiculos(Dd_vcl *reg, FILE *b_arq);
void imprime_registro_veiculos(Cb_vcl *cab, Dd_vcl *reg);
int checa_impressao_veiculos(char *busca, char *campo, Dd_vcl *reg);
void recebe_registro_ep_veiculos(Dd_vcl *reg);




#endif /* __VEICULOS_H__ */