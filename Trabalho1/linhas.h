/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções relacionadas
    ao arquivo de linhas assim como a estrutura de seu registro
*/
#ifndef __LINHAS_H__
#define __LINHAS_H__

typedef struct cabecalho_linhas{        //Elementos que compõem o registro de cabeçalho do arquivo de linhas
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
    char *nomeLinha;
    char *corLinha;
    char removido;
    int tamanhoRegistro;
    int tamanhoNome;
    int tamanhoCor;
}Dd_ln;
                        //Abaixo, temos o cabeçalho das funções do "linhas.c"






#endif /* __LINHAS_H__ */