#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "inimigos.h"
#include "personagem.h"
#include "desenho.h"
using namespace std;


/*...............................
****ARQUIVO PRINCIPAL DO JOGO****
...............................*/


/*********************VARIAVEIS DE CONTROLE*******************/
//variaveis controle
GLint pause=0,vidas=3,tempo=1,reinicio=0;
//variaveis de imagem
GLint imgVidas,imgFundo,imgMenu,imgComoJogar,imgSelecaoPersonagem,imgConfirmaPersonagem,imgPause,imgPerdeuVida;
GLint imgPerdeuJogo,imgGanhouJogo,imgConfirmaSaida;
//variavel de tela
enum Tela { MENU, JOGO,COMO_JOGAR,SELECIONAR_PERSONAGEM,CONFIRMAR_PERSONAGEM,PERDEU_VIDA,PAUSE, VITORIA, GAMEOVER,CONFIRMAR_SAIDA };
Tela telaAtual = MENU;
//tamanho lado do quadrado
GLint lado=100;
//cheat cima,baixo,100
GLint cheat=0;

/************************************************************/


/**************************INIMIGO***************************/
//vetor com posiçoes aleatoria de 1000 objetos
Inimigo inimigo[1000];
//controle criação
GLint indexCriar=0;
GLint devoCriar=0,imgJapaPF,imgJuizMoro;
//controle movimento de queda
GLint controleCair[1000],indexCair=0;
GLfloat velocidade=3;
/***********************************************************/

/***************************PERSONAGEM**********************/
Personagem personagem;
GLint imgPersonagem;
GLint escolha_Personagem;
/***********************************************************/

//setup inicial
void setup(){
	setupInimigo(inimigo,&imgJapaPF,&imgJuizMoro);
	setupDesenho(&imgFundo,&imgVidas,&imgMenu,&imgComoJogar,&imgSelecaoPersonagem,&imgConfirmaPersonagem,
					&imgPause,&imgPerdeuVida,&imgPerdeuJogo,&imgGanhouJogo,&imgConfirmaSaida);
}

//funçoes de desenhar na tela
void desenhaTela(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1,1,1,1);
	switch(telaAtual){
		case MENU:
			desenhaFundo(&imgMenu);
			break;

		case JOGO:
			desenhaFundo(&imgFundo);
			desenhaTempo(&tempo);
			glColor4f(1,1,1,1);
			desenhaVidas(&vidas,&imgVidas);
			//quadrados caindo...
			if(devoCriar==1){
				desenhaQuadradoInimigo(inimigo,controleCair,&indexCair,indexCriar,&lado,&imgJapaPF,&imgJuizMoro);
				desenhaCairInimigo(inimigo,controleCair,&indexCair,&lado,&imgJapaPF,&imgJuizMoro);
				indexCriar++;
				devoCriar=0;
			}
			else{
				desenhaCairInimigo(inimigo,controleCair,&indexCair,&lado,&imgJapaPF,&imgJuizMoro);
			}
			//personagem
			desenhaPersonagem(personagem,&imgPersonagem,&lado);
			break;

		case COMO_JOGAR:
			desenhaFundo(&imgComoJogar);
			break;

		case SELECIONAR_PERSONAGEM:
			desenhaFundo(&imgSelecaoPersonagem);
			break;

		case CONFIRMAR_PERSONAGEM:
			desenhaFundo(&imgConfirmaPersonagem);
			break;

		case PERDEU_VIDA:
			desenhaFundo(&imgPerdeuVida);
			break;

		case PAUSE:
			desenhaFundo(&imgPause);
			break;

		case VITORIA:
			desenhaFundo(&imgGanhouJogo);
			break;

		case GAMEOVER:
			desenhaFundo(&imgPerdeuJogo);
			break;

		case CONFIRMAR_SAIDA:
			desenhaFundo(&imgConfirmaSaida);
			break;

	}
	glutSwapBuffers();
}

//ajuste de tela
void ajustaTela(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//define eixo x,y
	glOrtho(-350,350,-350,350,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//timer inimigo tele guiado
void timerCriarInimigoTeleguiado(int idx){
	if(pause==0 && reinicio==0){
		glutTimerFunc(tempoCriaNovoInimigoTeleguiado,timerCriarInimigoTeleguiado,0);
		devoCriar=1;
		inimigo[indexCriar].tipo=JuizMoro;
	}
}
//timer que controla barra de tempo
void timerTempo(int idx){
	if(pause==0 && reinicio==0){
		tempo++;
		glutTimerFunc(1009,timerTempo,0);
		if(tempo==70){
			telaAtual=VITORIA;
		}
	}
}

//timer para permitir criar novo inimigo caindo
void timerCriar(int idx){
	if(pause==0 && reinicio==0){
		glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
		devoCriar=1;
		glutPostRedisplay();
	}	
}

//funçao de reboot apos perder uma vida
void rebootParcialTirandoVida(){
	setup();
	tempo=1;
	vidas--;
	indexCair=0;
	indexCriar=0;
	devoCriar=1;
}

//funçao que atualiza tela e faz inimigos cairem
void fazCair(){
	GLint i;
	if(pause==0 && reinicio==0){
		for(i=0;i<indexCair;i++){
			if(inimigo[controleCair[i]].tipo==JuizMoro && inimigo[controleCair[i]].y >= -100){
				inimigo[controleCair[i]].x=personagem.x;
			}
			cairInimigo(&indexCair,inimigo,controleCair,&velocidade,i);
			if(cheat<5 && personagem.x+lado>inimigo[controleCair[i]].x && personagem.x<inimigo[controleCair[i]].x+lado && (personagem.y+lado>inimigo[controleCair[i]].y && personagem.y<inimigo[controleCair[i]].y)){
				if(vidas>0){
					telaAtual=PERDEU_VIDA;
					tempo=1;
				}
				else
					telaAtual=GAMEOVER;
			}
		}
	}
	//printf("%d\n",cheat );
	glutPostRedisplay();
}

//movimentos do personagem
void movePersonagem(int tecla,int x,int y){
	if(tecla==GLUT_KEY_LEFT){
		if(personagem.x>-330 && pause==0)
			personagem.x-=20;
	}
	if(tecla==GLUT_KEY_RIGHT){
		if(personagem.x<250 && pause==0)
			personagem.x+=20;
	}
	if(tecla==GLUT_KEY_UP && cheat==0){
		cheat++;
	}
	if(tecla==GLUT_KEY_DOWN && cheat==1){
		cheat++;
	}
	//if(tecla){
	//	cheat=0;
	//}
}

//teclas de suporte no jogo
void teclasJogo(unsigned char tecla,int x,int y){
	if(tecla==27){
		telaAtual=CONFIRMAR_SAIDA;
		reinicio=1;
		setup();
		//confirmar saida
	}
	if(tecla && tecla!='1' && tecla!='0'){
		cheat=0;
	}
	if(tecla=='1' && cheat==2){
		cheat++;
	}
	if(tecla=='0' && (cheat==3 || cheat==4)){
		cheat++;
	}
	switch(telaAtual){
		case JOGO:
			if(tecla=='p' || tecla=='P'){ 
				if(pause==0){
					pause=1;
					telaAtual=PAUSE;
				}
			}
				
			if(tecla=='r' || tecla=='R'){
				telaAtual=SELECIONAR_PERSONAGEM;
				reinicio=1;
				setup();
				
			}
			break;

		case COMO_JOGAR:
			if(tecla=='m'){
				telaAtual=MENU;
				
			}

		case SELECIONAR_PERSONAGEM:
			if(tecla=='1'){
				escolha_Personagem=LULA;
				printf("%d\n",escolha_Personagem );
				telaAtual=CONFIRMAR_PERSONAGEM;
				
			}
			if(tecla=='2'){
				escolha_Personagem=AECIO;
				telaAtual=CONFIRMAR_PERSONAGEM;
				printf("%d\n",escolha_Personagem );
				
			}
			break;

		case CONFIRMAR_PERSONAGEM:
			if(tecla==13){//enter
				setup();
				reinicio=0;
				tempo=0;
				vidas=3;
				telaAtual=JOGO;
				indexCair=0;
				indexCriar=0;
				devoCriar=1;
				telaAtual=JOGO;
				setupPersonagem(&imgPersonagem,&personagem.y,&escolha_Personagem);
				//controle de tempo para criação
				glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
				glutTimerFunc(tempoCriaNovoInimigoTeleguiado,timerCriarInimigoTeleguiado,0);
				//timer para barra de tempo
				glutTimerFunc(1009,timerTempo,0);
				
			}
			if(tecla=='m' || tecla=='M'){
				telaAtual=MENU;
				
			}
			break;

		case PERDEU_VIDA:
			if(tecla==13){
				telaAtual=JOGO;
				rebootParcialTirandoVida();
				

			}
			break;

		case PAUSE:
			if(tecla=='p' || tecla=='P'){ 
				pause=0;
				telaAtual=JOGO;
				glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
				glutTimerFunc(tempoCriaNovoInimigoTeleguiado,timerCriarInimigoTeleguiado,0);
				glutTimerFunc(1009,timerTempo,0); 
				
			}
			break;

		case GAMEOVER:
			if(tecla=='r' || tecla=='R'){
				telaAtual=SELECIONAR_PERSONAGEM;
				reinicio=1;
				setup();
				
			}
		case VITORIA:
			if(tecla=='r' || tecla=='R'){
				telaAtual=SELECIONAR_PERSONAGEM;
				reinicio=1;
				setup();
				
			}
			break;
		case CONFIRMAR_SAIDA:
			if(tecla==13){
				exit(0);
			}
			if(tecla== 'm' || tecla=='M'){
				telaAtual=MENU;
				reinicio=1;
				setup();
				
			}
			break;
	}
	glutPostRedisplay();
}

void mouseMenu(int button, int state, int x, int y){
	//controle clique no MENU
	GLint MenuXPlay=247,MenuYPlay=190;
	GLint MenuXPlayFinal=479,MenuYPlayFinal=235;
	GLint MenuXComo_Jogar=122,MenuYComo_Jogar=373;
	GLint MenuXComo_JogarFinal=585, MenuYComo_JogarFinal=418;
	if(telaAtual==MENU){
		if((x>MenuXPlay && x<MenuXPlayFinal) && (y>MenuYPlay && y<MenuYPlayFinal)){
			telaAtual=SELECIONAR_PERSONAGEM;
		}
		if((x>MenuXComo_Jogar && x<MenuXComo_JogarFinal) && (y>MenuYComo_Jogar && y<MenuYComo_JogarFinal)){
			telaAtual=COMO_JOGAR;
		}
	}
}

int main(int argc, char **argv){
	srand(time(0));
	//INIT
	glutInit(&argc,argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//usando buffer duplo
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//tamanho da tela
	glutInitWindowSize(700,700);
	glutCreateWindow("Fuga Corrupta");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	setup();

	//callbacks
	glutDisplayFunc(desenhaTela);
	glutReshapeFunc(ajustaTela);
	glutMouseFunc(mouseMenu);
	glutKeyboardFunc(teclasJogo);
	glutSpecialFunc(movePersonagem);
	glutIdleFunc(fazCair);
	

	glutMainLoop();
	return 0;
}