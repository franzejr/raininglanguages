/*
 *  Importer.h
 *  raininglanguages
 *
 *	Classe com funcoes para importar do arquivo de strings e retornar essas strings 
 *	que foram geradas pela expressao regular
 *
 */

#include <vector>
#include <string>
#include <set>

using namespace std;

class Importer {
public:
	/*
	 Metodo que pega todas as palavras do arquivo e retorna um vetor com essas palavras
	 */
	set<string> getPalavras(string path);
	/*
	 Metodo que gera o arquivo, executando o script python que dado uma ER ele gera as palavras dessa ER
	 */
	void gerarArquivoComPalavras(string regex);
};
