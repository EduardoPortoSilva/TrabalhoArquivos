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

void carrega_veiculos(){                                            //Essa função irá criar o arquivo .bin de veículos ao percorrer       
    Cb_vcl cabecalho;                                               //o arquivo .csv
    Dd_vcl registro;
    FILE *arq = NULL, *nv_arq = NULL;
    long long int final;
    char *nm_arq, *nm_nv_arq;                                       //Usaremos "nomes_arqs_veiculos" para receber o nome dos arquivos
    if(nomes_arqs_veiculos(&arq, nv_arq, &nm_arq, &nm_nv_arq) < 0)  //e verificar se o .csv existe ou não
        return;
    else
        nv_arq = fopen(nm_nv_arq, "wb+");

    fseek(arq, 0, SEEK_END);                                        //Com o "fseek", obteremos o byte referente ao final do arquivo
    final = ftell(arq);                                             //e o usaremos como delimitador no loop
    fseek(arq, 0, SEEK_SET);

    ler_cabecalho_csv_veiculos(&cabecalho, arq);                    //Primeiro, leremos o registro de cabeçalho e o escreveremos
    fwrite(&cabecalho, sizeof(Cb_vcl), 1, nv_arq);
    while(final - 1 > ftell(arq)){                                  //Com o uso do "ftell", checaremos a nossa atual posição no .csv
        recebe_registro_csv_veiculos(&registro, arq);               //A cada iteração, "recebe_registro_csv_veiculos" e "manipula_campos_veiculos"
        manipula_campos_veiculos(&cabecalho, &registro);            //irão receber e manipular os campos de novos registros, atualizando também as
        preenche_dados_bin_veiculos(&registro, nv_arq);             //informações do registro de cabeçalho. Depois de tratar eventuais campos nulos,
        cabecalho.byteProxReg = ftell(nv_arq);                      //usaremos "preenche_dados_bin_veiculos" para inserir o registro no arquivo .bin
    }

    cabecalho.status = '1';                                         //Voltaremos para o começo do arquivo para alterar o cabeçalho, agora completo
    fseek(nv_arq, 0, SEEK_SET);
    fwrite(&cabecalho, sizeof(Cb_vcl), 1, nv_arq);
    fclose(nv_arq);                                                 //Fecharemos os arquivos e usaremos "binarioNaTela" para obtermos o resultado
    fclose(arq);
    binarioNaTela(nm_nv_arq);
    free(nm_arq);
    free(nm_nv_arq);
}

void dados_veiculos(){                                              //Essa função imprimirá os registros não excluídos do arquivo de veiculos
    Cb_vcl cabecalho;
    Dd_vcl registro;
    long long int final;
    char *nm_arq = (char *) malloc(16 * sizeof(char));              //Primeiro, receberemos o nome do arquivo
    scanf(" %s", nm_arq);

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

    ler_cabecalho_bin_veiculos(&cabecalho, b_arq);                  //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_bin_veiculos"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                   //Usando o offset final como delimitador, iremos continuar a ler registros
        recebe_registro_bin_veiculos(&registro, b_arq);             //com "recebe_registro_bin_veiculos" e, caso não tenha sido removido,
        if(registro.removido != '0')                                //imprimiremos suas informações com "imprime_registro_veiculos"
            imprime_registro_veiculos(&cabecalho, &registro);
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

    ler_cabecalho_bin_veiculos(&cabecalho, b_arq);                  //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_bin_veiculos"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                                               //Usando o offset final como delimitador, iremos continuar
        recebe_registro_bin_veiculos(&registro, b_arq);                                         //a ler registros com "recebe_registro_bin_veiculos".
        if(checa_impressao_veiculos(busca, campo, &registro) == 0 && registro.removido == '0')  //Usaremos "checa_impressao_veiculos" para verificar se
            printf("Registro inexistente.\n");                                                  //o registro atual possui ou não o valor buscado
        else if(checa_impressao_veiculos(busca, campo, &registro) == 0 && registro.removido != '0')
            imprime_registro_veiculos(&cabecalho, &registro);
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
    ler_cabecalho_bin_veiculos(&cabecalho, b_arq);                  //Receberemos o cabeçalho do arquivo, pois teremos que mudá-lo no final
    fseek(b_arq, 0, SEEK_END);
    cabecalho.nroRegistros += n_registers;                          //Atualizaremos o número total de registros

    while(n_registers != 0){                                        //Com esse while, usaremos "recebe_registro_ep_veiculos" para receber os valores
        recebe_registro_ep_veiculos(&registro);                     //dos campos do registro a partir da entrada padrão e o colocaremos no arquivo
        preenche_dados_bin_veiculos(&registro, b_arq);              //com "preenche_dados_bin_veiculos"
        n_registers--;
    }
    cabecalho.byteProxReg = ftell(b_arq);                           //Por fim, atualizaremos o "byteProxReg" do cabeçalho, o escreveremos mais
    fseek(b_arq, 0, SEEK_SET);                                      //uma vez no arquivo, em sua devida posição
    fwrite(&cabecalho, sizeof(Cb_vcl), 1, b_arq);
    fclose(b_arq);                                                  //Fecharemos o arquivo e usaremos "binarioNaTela" para obter o resultado
    binarioNaTela(nm_arq);
    free(nm_arq);
}
void carrega_linhas(){                                              //Essa função irá criar o arquivo .bin de linhas ao percorrer
    Cb_ln cabecalho;                                                //o arquivo .csv
    Dd_ln registro;
    FILE *arq = NULL, *nv_arq = NULL;
    long long int final;
    char *nm_arq, *nm_nv_arq;                                       //Usaremos "nomes_arqs_linhas" para receber o nome dos arquivos
    if(nomes_arqs_linhas(&arq, nv_arq, &nm_arq, &nm_nv_arq) < 0)    //e verificar se o .csv inserido existe ou não
        return;
    else
        nv_arq = fopen(nm_nv_arq, "wb+");

    fseek(arq, 0, SEEK_END);                                        //Com o "fseek" iremos obter o byte final do arquivo e o usaremos
    final = ftell(arq);                                             //como delimitador para o loop
    fseek(arq, 0, SEEK_SET);

    ler_cabecalho_csv_linhas(&cabecalho, arq);                      //Primeiro, leremos o registro de cabeçalho e o escreveremos
    fwrite(&cabecalho, sizeof(Cb_ln), 1, nv_arq);
    while(final - 1 > ftell(arq)){                                  //Com o uso do "ftell", checaremos nossa posição atual no .csv
        recebe_registro_csv_linhas(&registro, arq);                 //A cada iteração, "recebe_registro_csv_linhas" e "manipula_campos_linhas"
        manipula_campos_linhas(&cabecalho, &registro);              //irão receber e manipular os campos de novos registros, atualizando também as
        preenche_dados_bin_linhas(&registro, nv_arq);               //informações do registro de cabeçalho. Depois de tratar eventuais campos nulos,
        cabecalho.byteProxReg = ftell(nv_arq);                      //usaremos "preenche_dados_bin_linhas" para inserir o registro no arquivo .bin
    }

    cabecalho.status = '1';                                         //Voltaremos para o começo do arquivo para alterar o cabeçalho, agora completo
    fseek(nv_arq, 0, SEEK_SET);
    fwrite(&cabecalho, sizeof(Cb_ln), 1, nv_arq);
    fclose(nv_arq);                                                 //Fecharemos os arquivos e usaremos "binarioNaTela" para obtermos o resultado
    fclose(arq);
    binarioNaTela(nm_nv_arq);
    free(nm_arq);
    free(nm_nv_arq);
}

void dados_linhas(){                                                //Essa função imprimirá os registros não excluídos do arquivo de linhas
    Cb_ln cabecalho;
    Dd_ln registro;
    long long int final;
    char *nm_arq = (char *) malloc(16 * sizeof(char));              //Primeiro, receberemos o nome do arquivo
    scanf(" %s", nm_arq);

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

    ler_cabecalho_bin_linhas(&cabecalho, b_arq);                    //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_bin_linhas"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                   //Usando o offset final como delimitador, iremos continuar a ler registros
        recebe_registro_bin_linhas(&registro, b_arq);               //com "recebe_registro_bin_linhas" e, caso não tenha sido removido, imprimiremos
        if(registro.removido != '0')                                //suas informações com "imprime_registro_linhas"
            imprime_registro_linhas(&cabecalho, &registro);
    }

    fclose(b_arq);
    free(nm_arq);
}

void busca_linhas(){                                                //Função que realizará uma busca no arquivo .bin de linhas
    Cb_ln cabecalho;
    Dd_ln registro;
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
    fseek(b_arq, 0, SEEK_END);                                      //Iremos usar o "fseek" para obtermos o offset do final do arquivo
    final  = ftell(b_arq);
    fseek(b_arq, 0, SEEK_SET);

    ler_cabecalho_bin_linhas(&cabecalho, b_arq);                    //Iremos ler o cabeçalho do arquivo com "ler_cabecalho_bin_linhas"
    if(cabecalho.nroRegistros <= 0){                                //e verificaremos se existem registros no arquivo
        printf("Registro inexistente.\n");
        fclose(b_arq);
        free(nm_arq);
        return;
    }

    while(final != ftell(b_arq)){                                   //Usando o offset final como delimitador, iremos continuar a ler
        recebe_registro_bin_linhas(&registro, b_arq);               //registros com "recebe_registro_bin_linhas". Usaremos "checa_impressao_linhas"
        if(checa_impressao_linhas(busca, campo, &registro) == 0 && registro.removido != '0')//para verificar se o registro atual possui ou não
            imprime_registro_linhas(&cabecalho, &registro);                                 //o valor buscado, no respectivo campo
    }
    fclose(b_arq);
    free(busca);
    free(nm_arq);
}

void inserir_linhas(){                                              //Função que irá inserir novos registros no arquivo binário de linhas
    Cb_ln cabecalho;
    Dd_ln registro;
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
    ler_cabecalho_bin_linhas(&cabecalho, b_arq);                    //Receberemos o cabeçalho do arquivo, pois teremos que mudá-lo no final
    fseek(b_arq, 0, SEEK_END);
    cabecalho.nroRegistros += n_registers;                          //Atualizaremos o número total de registros

    while(n_registers != 0){                                        //Com esse while, usaremos "recebe_registro_ep_linhas" para receber os valores dos
        recebe_registro_ep_linhas(&registro);                       //campos do registro a partir da entrada padrão e o colocaremos no arquivo
        preenche_dados_bin_linhas(&registro, b_arq);                //com "preenche_dados_bin_linhas"
        n_registers--;
    }
    cabecalho.byteProxReg = ftell(b_arq);                           //Por fim, atualizaremos o "byteProxReg" do cabeçalho, o escreveremos mais
    fseek(b_arq, 0, SEEK_SET);                                      //uma vez no arquivo, em sua devida posição
    fwrite(&cabecalho, sizeof(Cb_ln), 1, b_arq);
    fclose(b_arq);                                                  //Fecharemos o arquivo e usaremos "binarioNaTela" para obter o resultado
    binarioNaTela(nm_arq);
    free(nm_arq);
}