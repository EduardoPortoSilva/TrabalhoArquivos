/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo .c contém funções relacionadas aos comandos que podem ser
    escolhidos durante a execução do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h"
#include "linhas.h"
#include "gerais.h"

void carrega_veiculos(){
    Cb_vcl cabecalho;
    Dd_vcl registro;
    FILE *arq = NULL, *nv_arq = NULL;
    long long int final;
    char *nm_arq, *nm_nv_arq;
    if(nomes_arqs_veiculos(arq, nv_arq, &nm_arq, &nm_nv_arq) < 0)
        return;
    else{
        arq = fopen(nm_arq, "r+");
        nv_arq = fopen(nm_nv_arq, "wb+");
    }
    fseek(arq, 0, SEEK_END);                                    //Essas 3 linhas são pra achar o final
    final = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    ler_cabecalho_veiculos_csv(&cabecalho, arq);
    escreve_cabecalho_bin(&cabecalho, nv_arq);
    while(final - 1 > ftell(arq)){
        recebe_registro_csv(&registro, arq);
        manipula_campos(&cabecalho, &registro);
        preenche_dados_bin(&registro, nv_arq);
        cabecalho.byteProxReg = ftell(nv_arq);
    }

    cabecalho.status = '1';
    fseek(nv_arq, 0, SEEK_SET);
    escreve_cabecalho_bin(&cabecalho, nv_arq);
    fecha_arquivos(arq, nv_arq);                            //Fechar os arqs pra poder chamar a função do monitor
    binarioNaTela(nm_nv_arq);
    libera_nomes_arquivos(nm_arq, nm_nv_arq);
}

void dados_veiculos(){
    Cb_vcl cabecalho;
    Dd_vcl registro;
    long long int final;
    char *nm_arq = (char *) malloc(14 * sizeof(char));
    scanf("%s ", nm_arq);

    FILE *b_arq = fopen(nm_arq, "rb");
    if(checa_status(b_arq) < 0){                                      //Pra ver se o arquivo n ta inconsistente
        free(nm_arq);
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(b_arq, 0, SEEK_END);
    final  = ftell(b_arq);
    fseek(b_arq, 0, SEEK_SET);

    ler_cabecalho_veiculos_bin(&cabecalho, b_arq);
    if(cabecalho.nroRegistros <= 0){
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final > ftell(b_arq)){
        recebe_registro_bin(&registro, b_arq);
        if(registro.removido != '0')
            imprime_registro(&cabecalho, &registro);
    }

    fclose(b_arq);
    free(nm_arq);
}