struct Personagem{
	float x;
	float y;
	int tamanho;
};

#define LULA 1
#define AECIO 2

void setupPersonagem(int *imgPersonagem,Personagem *personagem,int *escolha);
void desenhaPersonagem(Personagem personagem,int *imgPesonagem);
