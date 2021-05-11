/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo contém a função "main" do nosso trabalho
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h"
#include "linhas.h"

int main(int argc, char *argv[]){
    int op;                                 //Na "main", receberemos o código da operação e chamaremos
    scanf("%d", &op);                       //a respectiva função por meio da switch-case

    switch(op){
        case 1:
            carrega_veiculos();
            break;
        case 2:
            carrega_linhas();
            break;
        case 3:
            dados_veiculos();
            break;
        case 4:
            dados_linhas();
            break;
        case 5:
            busca_veiculos();
            break;
        case 6:
            busca_linhas();
            break;
        case 7:
            inserir_veiculos();
            break;
        case 8:
            inserir_linhas();
            break;
        default:
            printf("Operação inválida\n");
            break;
    }

    return 0;
}