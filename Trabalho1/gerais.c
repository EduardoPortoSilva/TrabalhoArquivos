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

int checa_status(FILE *arq){								//Função para verificar o campo "status" do cabeçalho dos arquivos
	char status;
	if(arq == NULL)	return -1;

	fread(&status, 1, 1, arq);								//Depois de verificar o "status", retornaremos o cursor para o
	fseek(arq, 0, SEEK_SET);								//começo do arquivo. Caso não seja possível abrir o arquivo, ou caso
	if(status == '1')										//o "status" seja inconsistente, retornaremos -1 para representar o erro
		return 0;
	else
		return -1;
}

int checa_nulo(char *str){									//Função que irá verificar se a string passada como parâmetro faz
	int i = 0;												//referência a um campo nulo ou não
	char nulo[] = "NULO";

	for(i = 0; i < 4; i++){									//Com esse simples "for" iremos comparar as posições
        if(str[i] != nulo[i])
            break;
    }
    if(i == 4)												//Retornaremos -1 caso seja nulo e 0 caso contrário
		return -1;
	else
		return 0;
}

void preenche_string_nula(char *str, int size){				//Essa função será usada para preencher os campos fixos que forem nulos
	str[0] = '\0';
	for(int i = 1; i < size; i++)
		str[i] = '@';
}

void preenche_lixo(char *str, int s_atual, int s_des){		//Essa função irá preencher os campos não utilizados das strings
	for(int i = s_atual; i < s_des; i++){					//de tamanho fixo
		if(i == s_atual)	str[i] = '\0';
		else	str[i] = '@';
	}
}

void copiar_string(char *str1, char *str2, int size){		//Essa função irá copiar a "str1" para a "str2"

	for(int i = 0; i < size; i++)
		str2[i] = str1[i];
}

char *trata_string(char *str, int size){					//Essa função irá manipular a string recebida para que ela possa ser 
	char *printable_str;									//impressa
	if(size <= 0 || str[0] == '\0'){						//Caso seja nula, receberá a string "campo_nulo"
		char *campo_nulo = malloc(21 * sizeof(char));
		strcpy(campo_nulo, "campo com valor nulo\0");
		return campo_nulo;
	}
	if(str[0] != '2'){										//Caso a string não seja nula e não seja uma data, usaremos "copiar_string"
		printable_str = malloc((size + 1) * sizeof(char));
		copiar_string(str, printable_str, size);
		printable_str[size] = '\0';
	}else{													//Caso seja uma data, chamaremos "manipula_data"
		printable_str = malloc(35 * sizeof(char));
		printable_str = manipula_data(str, printable_str);
	}

	return printable_str;
}

char *manipula_data(char *str, char *print){										//Essa função irá receber e alterar a string
	int aux;																		//referente à data com auxílio dessas strings
	char janeiro[] = "janeiro", fevereiro[] = "fevereiro", marco[] = "março";		//auxiliares
	char abril[] = "abril", maio[] = "maio", junho[] = "junho", julho[] = "julho";
	char agosto[] = "agosto", setembro[] = "setembro", outubro[] = "outubro";
	char novembro[] = "novembro", dezembro[] = "dezembro", conector[] = " de ";

	print[0] = str[8];									//Começaremos a nova string com a data e usaremos "strcat" para concatenar
	print[1] = str[9];									//a string atual e "conector"
	print[2] = '\0';
	strcat(print, conector);
	if(str[6] == '0')		strcat(print, outubro);		//Com essa sequência de ifs, verificaremos o mês e usaremos a string
	else if(str[6] == '9')	strcat(print, setembro);	//correspondente para concatenar
	else if(str[6] == '8')	strcat(print, agosto);
	else if(str[6] == '7')	strcat(print, julho);
	else if(str[6] == '6')	strcat(print, junho);
	else if(str[6] == '5')	strcat(print, maio);
	else if(str[6] == '4')	strcat(print, abril);
	else if(str[6] == '3')	strcat(print, marco);
	else if(str[6] == '2' && str[5] == '0')	strcat(print, fevereiro);
	else if(str[6] == '1' && str[5] == '0')	strcat(print, janeiro);
	else if(str[6] == '1' && str[5] == '1')	strcat(print, novembro);
	else if(str[6] == '2' && str[5] == '1')	strcat(print, dezembro);
	strcat(print, conector);							//Depois, iremos concatenar "conector" mais uma vez e inserir, por fim,
	aux = strlen(print);								//o ano e o '\0'
	print[aux] = str[0];
	print[aux + 1] = str[1];
	print[aux + 2] = str[2];
	print[aux + 3] = str[3];
	print[aux + 4] = '\0';
	print = realloc(print, (aux + 5) * sizeof(char));

	return print;
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