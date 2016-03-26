#define TOPO_TELA 350
#define FUNDO_TELA -350
#define ESQUERDA_TELA -350
#define DIREITA_TELA 350
#define CENTRO 0

void setupDesenho(int *imgFundo,int *imgVidas,int *imgMenu,int *imgComoJogar,int *imgSelecaoPersonagem,
					int *imgDificuldade,int *imgPause,int *imgPerdeuVida,int *imgPerdeuJogo,int *imgGanhouJogo,int *imgConfirmaSaida,int *imgConfirmaReboot);
void desenhaVidas(int *vidas,int *imgVidas);
void desenhaFundo(int *imgFundo,float *spriteBegin,float *spriteEnd);
void desenhaTempo(int *tempo);
