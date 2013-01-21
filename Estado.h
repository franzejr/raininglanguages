#ifndef ESTADO_H
#define ESTADO_H

using namespace std;

class Estado{
public:
	Estado *vizinho1, *vizinho2;
	char letraDeTransicao1, letraDeTransicao2;
	bool isFinal;
};

#endif
