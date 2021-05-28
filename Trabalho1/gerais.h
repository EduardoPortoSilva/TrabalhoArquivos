/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções disponibilizadas
    no run.codes e outras que utilizamos para ambos os arquivos
*/
#ifndef __GERAIS_H__
#define __GERAIS_H__
                        //Abaixo, temos o cabeçalho das funções do "gerais.c"
int checa_status(FILE *arq);
int checa_nulo(char *str);
void preenche_string_nula(char *str, int size);
void preenche_lixo(char *str, int s_atual, int s_des);
void copiar_string(char *str1, char *str2, int size);
char *trata_string_veiculos(char *str, int size);
char *trata_string_linhas(char *str, int size);
char *manipula_data(char *str, char *print);



void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

#endif /* __GERAIS_H__ */