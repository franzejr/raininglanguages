/*
 *  Automato.cpp
 *  raininglanguages
 *
 */

#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>

#include "Automato.h"
#include "Estado.h"

Automato::Automato(int qtdEstados) : qtdEstados(qtdEstados){
	srand(time(NULL));
	int qtdSimbolos = 2, indiceRandom; //So iremos utilizar 2, pois eh o que vemos comumente
	//Simbolos que poderemos utilizar
	char simbolos[qtdSimbolos];
	
	simbolos[0] = 'a';
	simbolos[1] = 'b';
	
	//Criando os estados do automato
	for (int i = 0; i < qtdEstados; i++) {
		estados.push_back(new Estado());
	}
	int x = rand()%qtdEstados;
	printf("estado final: %d\n",x);
	estados.at(x)->isFinal = 1;
	
	bool isFinal;
	system("clear");
	printf("##########Descricao dos Estados do Automato##########"); 
	for (int i = 0; i < qtdEstados; i++) {
		printf("\nEstado %d\n",i);
		//Dizendo se o estado eh um estado de aceitacao ou nao
		if (!estados.at(i)->isFinal)
		{
			isFinal = rand() % 1;
			estados.at(i)->isFinal = isFinal;
		}
		printf("Eh final: %s\n",estados.at(i)->isFinal ? "Sim" : "Nao");
		//obs: podem ser criados muitos estados de aceitação.

		//Pegando um indice qualquer para ser vizinho
		indiceRandom = random() %qtdEstados;
		
		printf("Vizinho a: %d\n",indiceRandom);
		
		estados.at(i)->vizinho1 = estados.at(indiceRandom);
		estados.at(i)->letraDeTransicao1 = simbolos[0];
		
		indiceRandom = random() %qtdEstados;
		printf("Vizinho b: %d\n",indiceRandom);
		
		estados.at(i)->vizinho2 = estados.at(indiceRandom);
		estados.at(i)->letraDeTransicao2 = simbolos[1];
	}
	printf("#####################################################\n");
	
	//Colocando as 5000 palavras dentro do conjunto de palavras que o automato retorna
	for (int i=0; i<5000; i++) palavrasDoAutomato.insert(getPalavra());
}

//Retorna o conjunto de palavras que o automato retorna
set<string> Automato::getPalavras(){
	return palavrasDoAutomato;
}

//Retorna uma unica palavra do automato
string Automato::getPalavra(){
	double probab;
	Estado *estadoAtual = estados.at(0), *vizinhoEscolhido;
	string palavraGerada = "",safeString = "",buffer  = "";
	char buffer2;
	
	while (1) {
		//Se a palavra gerada atual eh maior que 50, entao nao pode
		if (palavraGerada.size() > 50) {
			if (safeString.size()==0) return "E";
			else if (safeString.size()>50) return "";
		}
		safeString.append(buffer);
		buffer.assign("");
		
		if(estadoAtual->isFinal){
				probab = ((double)(rand()%1000001))/1000000.0;
				if (probab < 0.25)
				{
					if (palavraGerada.size()==0) return "E";
					if (palavraGerada.size()<=50) return palavraGerada;
					return "";
				}
		}
		
		probab = ((double)(rand()%1000001))/1000000.0;
		
		if (probab < 0.5)
		{//Vamos pelo vizinho 1
			vizinhoEscolhido = estadoAtual->vizinho1;
			buffer2 = estadoAtual->letraDeTransicao1;
			//Vamos botar no buffer o caracter da transicao
		}
		else
		{//Vamos pelo vizinho 2
			vizinhoEscolhido = estadoAtual->vizinho2;
			buffer2 = estadoAtual->letraDeTransicao2;
			//Vamos botar no buffer o caracter da transicao
		}

		buffer.push_back(buffer2);
		palavraGerada.push_back(buffer2);
		estadoAtual = vizinhoEscolhido;
	}
	
	if (palavraGerada.size()==0) return "E";
	if (palavraGerada.size()<=50) return palavraGerada;
	return "";
}

//
bool Automato::palavraPertence(string palavra)
{
	if (palavra == "E" && estados.at(0)->isFinal) return true;
	Estado *estadoAtual = estados.at(0);
	char *letra = &(palavra.at(0));
	int count = 0;
	
	while (count < palavra.size())
	{
		if (*letra == estadoAtual->letraDeTransicao1) estadoAtual = estadoAtual->vizinho1;
		else estadoAtual = estadoAtual->vizinho2;
		letra++;
		count++;
	}
	
	return estadoAtual->isFinal;
}
