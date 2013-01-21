#ifndef AUTOMATO_H
#define AUTOMATO_H
/*
 *  Automato.h
 *  raininglanguages
 *
 *Representacao de um automato
 *
 */
#include <string>
#include <vector>
#include <set>
#include "Estado.h"

using namespace std;

class Automato {
public:
	/*
	 
	 */
	Automato(int qtdEstados);
	
	
	/*
	 Metodo que executa o automato retornando uma unica palavra
	 */
	
	string getPalavra();
	
	/*
	 Retorna um grande numero de palavras aleatorias geradas pelo automato
	 Eh com esse metodo que vamo saber se a expressao regular satisfaz esse conjunto
	 de palavras
	 */
	set<string> getPalavras();
	
	bool palavraPertence(string palavra);
	
	//Conjunto de palavras retornadas pelo automato.
	set<string> palavrasDoAutomato;
	
	//Conjunto de Estados do automato
	vector<Estado*> estados;
	
	//Quantidade de Estados
	int qtdEstados;
	
private:
	
	//Palavra que esta sendo construido pelo automato
	string palavra;
	
	/*
	 Metodo que simula a transicao entre um estado e outro
	 */
	void iterate();
};
#endif
