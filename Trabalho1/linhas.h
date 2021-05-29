/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções relacionadas
    ao arquivo de linhas assim como a estrutura de seu registro
*/
#ifndef __LINHAS_H__
#define __LINHAS_H__

typedef struct __attribute__((__packed__)) cabecalho_linhas{        //Elementos que compõem o registro de cabeçalho do arquivo de linhas
    char status;
    long long int byteProxReg;
    int nroRegistros;
    int nroRegRemovidos;
    char descreveCodigo[15];
    char descreveCartao[13];
    char descreveNome[13];
    char descreveCor[24];
}Cb_ln;

typedef struct dados_linhas{            //Elementos que compõem o registro de dados do arquivo de linhas
    int codLinha;
    char aceitaCartao;
    char nomeLinha[100];
    char corLinha[100];
    char removido;
    int tamanhoRegistro;
    int tamanhoNome;
    int tamanhoCor;
}Dd_ln;
                        //Abaixo, temos o cabeçalho das funções do "linhas.c"
int nomes_arqs_linhas(FILE **arq, FILE *nv_arq, char **nm_arq, char **nm_nv_arq);
void ler_cabecalho_csv_linhas(Cb_ln *cab, FILE *arq);
void recebe_registro_csv_linhas(Dd_ln *reg, FILE *arq);
void manipula_campos_linhas(Cb_ln *cab, Dd_ln *reg);
void preenche_dados_bin_linhas(Dd_ln *reg, FILE *b_arq);
void ler_cabecalho_bin_linhas(Cb_ln *cabecalho, FILE *b_arq);
void recebe_registro_bin_linhas(Dd_ln *reg, FILE *b_arq);
void imprime_registro_linhas(Cb_ln *cab, Dd_ln *reg);
int checa_impressao_linhas(char *busca, char *campo, Dd_ln *reg);
void recebe_registro_ep_linhas(Dd_ln *reg);

#endif /* __LINHAS_H__ */