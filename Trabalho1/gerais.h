/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo header contém o cabeçalho das funções disponibilizadas
    no run.codes e outras que utilizamos para ambos os arquivos
*/
#ifndef __GERAIS_H__
#define __GERAIS_H__
                        //Abaixo, temos o cabeçalho das funções do "gerais.c"
void libera_nomes_arquivos(char *n1, char *n2);
void fecha_arquivos(FILE *p1, FILE *p2);
int checa_status(FILE *arq);
int checa_nulo(char *str);
void preenche_string_nula(char *str, int size);
void copiar_string(char *str1, char *str2, int size);


void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

#endif /* __GERAIS_H__ */