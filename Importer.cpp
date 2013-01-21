/*
 *  Importer.cpp
 *  raininglanguages
 *
 *	Classe com funcoes para importar do arquivo de strings e retornar essas strings 
 *	que foram geradas pela expressao regular
 *
 */

#include <cstdio>
#include <cstdlib>
#include <set>
#include "Importer.h"

set<string> Importer::getPalavras(string path){
	//Se quiser depois pasasr por parametro, mas a principio nao estamos passando, porque sempre verificamos um arquivo fixo.
	path = "strings";
	
	char temp[53];
	set<string> strings;
    //printf("Vai agora criar o arquivo que contem as strings");
	FILE *arquivo = fopen("strings","r");
	//se quisermos modificar a quantidade de palavras, basta mudar aqui e no generate_strings do Python
	for (int i=0; i< 5000; i++) {
		fscanf(arquivo, "%s", temp);
		string str_temp = temp;
		strings.insert(str_temp);
	}
	return strings;
}

void Importer::gerarArquivoComPalavras(string regex){
    //printf("Vai executar o comando system para poder pegar depois");
	string command = "python generate_strings.py ";
	command += "'";
	command += regex;
	command += "'";
	system(command.c_str());
}
