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
    if(nomes_arqs_veiculos(&arq, nv_arq, &nm_arq, &nm_nv_arq) < 0)
        return;
    else{
        nv_arq = fopen(nm_nv_arq, "wb+");
    }

    fseek(arq, 0, SEEK_END);
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
    fclose(nv_arq);
    fclose(arq);
    binarioNaTela(nm_nv_arq);
    free(nm_arq);
    free(nm_nv_arq);
}

void dados_veiculos(){                                              //Essa função realizará a busca dos registros no arquivo binário
    Cb_vcl cabecalho;                                               //de veículos
    Dd_vcl registro;
    long long int final;
    char *nm_arq = (char *) malloc(16 * sizeof(char));              //Primeiro, receberemos o nome do arquivo
    scanf("%s ", nm_arq);

    FILE *b_arq = fopen(nm_arq, "rb+");                             //Tentaremos abrir o arquivo e usaremos "checa_status" para
    if(checa_status(b_arq) < 0){                                    //garantir que podemos acessá-lo sem erros
        free(nm_arq);
        fclose(b_arq);
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(b_arq, 0, SEEK_END);                                      //Iremos usar o fseek para obtermos o offset do final do arquivo
    final  = ftell(b_arq);
    fseek(b_arq, 0, SEEK_SET);

    ler_cabecalho_veiculos_bin(&cabecalho, b_arq);                  //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_veiculos_bin"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                   //Usando o offset final como delimitador, iremos continuar a ler registros
        recebe_registro_bin(&registro, b_arq);                      //com "recebe_registro_bin" e, caso não tenha sido removido, imprimiremos
        if(registro.removido != '0')                                //suas informações com "imprime_registro"
            imprime_registro(&cabecalho, &registro);
    }

    fclose(b_arq);
    free(nm_arq);
}

void busca_veiculos(){                                              //Função que irá receber o valor de determinado campo
    Cb_vcl cabecalho;                                               //entre os registros no arquivo binário de veículos
    Dd_vcl registro;
    FILE *b_arq = NULL;
    long long int final;
    char *nm_arq = (char *) malloc(16 * sizeof(char));
    char *busca = (char *) calloc(100, sizeof(char));
    char campo[100];

    scanf("%s %s ", nm_arq, campo);                                 //Primeiro, receberemos o nome do arquivo e o nome do campo
    scan_quote_string(busca);                                       //com o "scanf" e o valor dele com "scan_quote_string"
    if(strlen(busca) == 0)  strcpy(busca, "NULO");
    b_arq = fopen(nm_arq, "rb+");
    if(checa_status(b_arq) < 0){                                    //"checa_status" garantirá que podemos acessar o arquivo sem erros
        free(nm_arq);
        free(busca);
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(b_arq, 0, SEEK_END);                                      //Iremos usar o fseek para obtermos o offset do final do arquivo
    final  = ftell(b_arq);
    fseek(b_arq, 0, SEEK_SET);

    ler_cabecalho_veiculos_bin(&cabecalho, b_arq);                  //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_veiculos_bin"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                   //Usando o offset final como delimitador, iremos continuar a ler
        recebe_registro_bin(&registro, b_arq);                      //registros com "recebe_registro_bin". Usaremos "checa_impressao"
        if(checa_impressao(busca, campo, &registro) == 0 && registro.removido == '0')   //para verificar se o registro atual possui ou não
            printf("Registro inexistente.\n");                                          //o valor buscado
        else if(checa_impressao(busca, campo, &registro) == 0 && registro.removido != '0')
            imprime_registro(&cabecalho, &registro);
    }
    fclose(b_arq);
    free(busca);
    free(nm_arq);
}

void inserir_veiculos(){                                            //Função que irá inserir novos registros no arquivo binário de veiculos
    Cb_vcl cabecalho;
    Dd_vcl registro;
    FILE *b_arq = NULL;
    int n_registers;
    char *nm_arq = (char *) malloc(16 * sizeof(char));

    scanf("%s %d ", nm_arq, &n_registers);                          //Primeiro, receberemos o nome do arquivo e a quantidade de novos registros,
    b_arq = fopen(nm_arq, "rb+");                                   //depois tentaremos abrir o arquivo e usaremos "checa_status" para
    if(checa_status(b_arq) < 0){                                    //garantir que podemos acessá-lo sem erros
        free(nm_arq);
        fclose(b_arq);
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    ler_cabecalho_veiculos_bin(&cabecalho, b_arq);                  //Receberemos o cabeçalho do arquivo, pois teremos que mudá-lo no final
    fseek(b_arq, 0, SEEK_END);
    cabecalho.nroRegistros += n_registers;                          //Atualizaremos o número total de registros

    while(n_registers != 0){                                        //Com esse while, usaremos "recebe_registro_ep" para receber os valores dos
        recebe_registro_ep(&registro);                              //campos do registro a partir da entrada padrão e o colocaremos no arquivo
        preenche_dados_bin(&registro, b_arq);                       //com "preenche_dados_bin"
        n_registers--;
    }
    cabecalho.byteProxReg = ftell(b_arq);                           //Por fim, atualizaremos o "byteProxReg" do cabeçalho, o escreveremos mais
    fseek(b_arq, 0, SEEK_SET);                                      //uma vez no arquivo, em sua devida posição
    escreve_cabecalho_bin(&cabecalho, b_arq);
    fclose(b_arq);                                                  //Fecharemos o arquivo e usaremos "binarioNaTela" para obter o resultado
    binarioNaTela(nm_arq);
    free(nm_arq);
}