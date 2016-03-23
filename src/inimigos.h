#define JapaPF 1
#define JuizMoro 2
//controle de tempo
#define tempoCriaNovoInimigo 1000
#define tempoCriaNovoInimigoTeleguiado 10000
struct Inimigo{
	float x;
	float y;
	int tipo;
};
void desenhaQuadradoInimigo(Inimigo *inimigo, int *controleCair,int *indexCair,int indexCriar,int *lado,int *imgJapaPF,int *imgJuizMoro);
void desenhaCairInimigo(Inimigo *inimigo,int *controleCair,int *indexCair,int *lado,int *imgJapaPF,int *imgJuizMoro);
void setupInimigo(Inimigo *inimigo, int *imgJapaPF,int *imgJuizMoro);
void cairInimigo(int *indexCair,Inimigo *inimigo,int *controleCair,float *velocidade,int i);
