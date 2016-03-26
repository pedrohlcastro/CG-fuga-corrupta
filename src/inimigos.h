#define JapaPF 1
#define JuizMoro 2

struct Inimigo{
	float x;
	float y;
	int tamanho;
	int tipo;
};

void desenhaQuadradoInimigo(Inimigo *inimigo, int *controleCair,int *indexCair,int indexCriar,int *imgJapaPF,int *imgJuizMoro);
void desenhaCairInimigo(Inimigo *inimigo,int *controleCair,int *indexCair,int *imgJapaPF,int *imgJuizMoro);
void setupInimigo(Inimigo *inimigo, int *imgJapaPF,int *imgJuizMoro);
void cairInimigo(int *indexCair,Inimigo *inimigo,int *controleCair,float *velocidade,int i);
