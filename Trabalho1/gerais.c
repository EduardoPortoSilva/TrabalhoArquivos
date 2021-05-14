/*
    Eduardo Henrique Porto Silva    NUSP 11796656
    Tulio Santana Ramos             NUSP 11795526

    Esse arquivo .c contém funções disponibilizadas no run.codes
    e outras funções utilizadas em ambos os arquivos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gerais.h"

void libera_nomes_arquivos(char *n1, char *n2){		//Função para liberar o nome do arquivo de entrada e o criado
	free(n1);
	free(n2);
}

void fecha_arquivos(FILE *p1, FILE *p2){			//Função para fechar o arquivo recebido e o criado
	fclose(p1);
	fclose(p2);
}

int checa_status(FILE *arq){						//Função para verificar o campo "status" do cabeçalho dos arquivos
	char status;
	if(arq == NULL)	return -1;

	//fread(&status, 1, 1, arq);						//Depois de verificar o "status", retornaremos o cursor para o
	//fseek(arq, 0, SEEK_SET);						//começo do arquivo. Caso não seja possível abrir o arquivo, ou caso
	//if(status == '1')								//o "status" seja inconsistente, retornaremos -1 para representar o erro
	//	return 0;
	//else
	//	return -1;
}

int checa_nulo(char *str){
	int i = 0;
	char nulo[] = "NULO";

	for(i = 0; i < 4; i++){
        if(str[i] != nulo[i])
            break;
    }
    if(i == 4)
		return -1;
	else
		return 0;
}

void preenche_string_nula(char *str, int size){
	for(int i = 0; i < size; i++){
		if(i == 0)	str[i] = '\0';
		else	str[i] = '@';
	}
}

void copiar_string(char *str1, char *str2, int size){

	for(int i = 0; i < size; i++)
		str2[i] = str1[i];
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}