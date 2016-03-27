#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <SFML/Audio.hpp>
#include "inimigos.h"
#include "personagem.h"
#include "desenho.h"
using namespace std;


/*...............................
****ARQUIVO PRINCIPAL DO JOGO****
...............................*/

#define ENTER 13
#define ESC 27


/*********************VARIAVEIS DE CONTROLE*******************/
//variaveis controle
GLint pause=0,vidas=3,tempo=1,reinicio=0;
//variaveis de imagem
GLint imgVidas,imgFundo,imgMenu,imgComoJogar,imgSelecaoPersonagem,imgDificuldade,imgPause,imgPerdeuVida;
GLint imgPerdeuJogo,imgGanhouJogo,imgConfirmaSaida,imgConfirmaReboot;
//variavel de tela
enum Tela { MENU, JOGO,COMO_JOGAR,SELECIONAR_PERSONAGEM,SELECIONAR_DIFICULDADE,PERDEU_VIDA,PAUSE, VITORIA, GAMEOVER,CONFIRMAR_SAIDA,CONFIRMAR_REBOOT };
Tela telaAtual = MENU;
//tamanho lado do quadrado
//GLint lado=90;
//cheat cima,baixo,100
GLint cheat=0;
//sprite menu
GLfloat spriteBegin=0,spriteEnd=0.5;
//contorle tempo
GLint tempoCriaNovoInimigo=1000;
GLint tempoCriaNovoInimigoTeleguiado=10000;

//musica
sf::Music musicCheat,musicGAME_OVER,musicJOGO,musicWIN,musicMENUS;
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
	setupDesenho(&imgFundo,&imgVidas,&imgMenu,&imgComoJogar,&imgSelecaoPersonagem,&imgDificuldade,
					&imgPause,&imgPerdeuVida,&imgPerdeuJogo,&imgGanhouJogo,&imgConfirmaSaida,&imgConfirmaReboot);
	musicCheat.openFromFile("sounds/cheat.ogg");
	musicGAME_OVER.openFromFile("sounds/gameover.ogg");
	musicJOGO.openFromFile("sounds/jogo.ogg");
	musicWIN.openFromFile("sounds/ganhou.ogg");
	musicMENUS.openFromFile("sounds/menus.ogg");
	musicMENUS.setLoop(true);
	musicMENUS.play();
}

//funçoes de desenhar na tela
void desenhaTela(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1,1,1,1);
	switch(telaAtual){
		case MENU:
			desenhaFundo(&imgMenu,&spriteBegin,&spriteEnd);
			break;

		case JOGO:
			desenhaFundo(&imgFundo,&spriteBegin,&spriteEnd);
			desenhaTempo(&tempo);
			glColor4f(1,1,1,1);
			desenhaVidas(&vidas,&imgVidas);
			//quadrados caindo...
			if(devoCriar==1){
				desenhaQuadradoInimigo(inimigo,controleCair,&indexCair,indexCriar,&imgJapaPF,&imgJuizMoro);
				desenhaCairInimigo(inimigo,controleCair,&indexCair,&imgJapaPF,&imgJuizMoro);
				indexCriar++;
				devoCriar=0;
			}
			else{
				desenhaCairInimigo(inimigo,controleCair,&indexCair,&imgJapaPF,&imgJuizMoro);
			}
			//personagem
			desenhaPersonagem(personagem,&imgPersonagem);
			break;

		case COMO_JOGAR:
			desenhaFundo(&imgComoJogar,&spriteBegin,&spriteEnd);
			break;

		case SELECIONAR_PERSONAGEM:
			desenhaFundo(&imgSelecaoPersonagem,&spriteBegin,&spriteEnd);
			break;

		case SELECIONAR_DIFICULDADE:
			desenhaFundo(&imgDificuldade,&spriteBegin,&spriteEnd);
			break;

		case PERDEU_VIDA:
			desenhaFundo(&imgPerdeuVida,&spriteBegin,&spriteEnd);
			break;

		case PAUSE:
			desenhaFundo(&imgPause,&spriteBegin,&spriteEnd);
			break;

		case VITORIA:
			desenhaFundo(&imgGanhouJogo,&spriteBegin,&spriteEnd);
			break;

		case GAMEOVER:
			desenhaFundo(&imgPerdeuJogo,&spriteBegin,&spriteEnd);
			break;

		case CONFIRMAR_SAIDA:
			desenhaFundo(&imgConfirmaSaida,&spriteBegin,&spriteEnd);
			break;
		case CONFIRMAR_REBOOT:
			desenhaFundo(&imgConfirmaReboot,&spriteBegin,&spriteEnd);
			break;

	}
	glutSwapBuffers();
}

//ajuste de tela
void ajustaTela(int width,int height){
	//codigo de terceiro =D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(width>height){
		glViewport((width-height)/2,0,height,height);
	}
	if(height>width){
		glViewport(0,(height-width)/2,width,width);
	}
	glMatrixMode(GL_PROJECTION);
	//FIM CODIGO DE TERCEIRO

	//define eixo x,y
	glOrtho(ESQUERDA_TELA,DIREITA_TELA,FUNDO_TELA,TOPO_TELA,-1,1);
	glMatrixMode(GL_MODELVIEW);
	
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
			musicJOGO.stop();
			musicWIN.play();
			//musicMENUS.play();
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
			if(inimigo[controleCair[i]].tipo==JuizMoro && inimigo[controleCair[i]].y >= (-1.5*personagem.tamanho)){
				inimigo[controleCair[i]].x=personagem.x;
			}
			cairInimigo(&indexCair,inimigo,controleCair,&velocidade,i);
			if(cheat<5 && personagem.x+personagem.tamanho>inimigo[controleCair[i]].x && personagem.x<inimigo[controleCair[i]].x+inimigo[controleCair[i]].tamanho && (personagem.y+personagem.tamanho>inimigo[controleCair[i]].y && personagem.y<inimigo[controleCair[i]].y)){
				if(vidas>0){
					musicJOGO.stop();
					musicMENUS.play();
					telaAtual=PERDEU_VIDA;
					tempo=1;
				}
				else{
					musicJOGO.stop();
					musicGAME_OVER.play();
					//musicMENUS.play();
					pause=1;
					telaAtual=GAMEOVER;
				}
			}
		}
	}
	glutPostRedisplay();
}

//movimentos do personagem
void teclasEspeciais(int tecla,int x,int y){
	//teclas controle personagem
	if(telaAtual==JOGO){
		if(tecla==GLUT_KEY_LEFT){
			//330
			if(personagem.x>ESQUERDA_TELA && pause==0)
				personagem.x-=20;
		}
		//250
		if(tecla==GLUT_KEY_RIGHT){
			if(personagem.x<DIREITA_TELA-personagem.tamanho && pause==0)
				personagem.x+=20;
		}
		if(tecla==GLUT_KEY_UP && cheat==0){
			cheat++;
		}
		if(tecla==GLUT_KEY_DOWN && cheat==1){
			cheat++;
		}
	}

	//teclas controle menus
	if(telaAtual==MENU || telaAtual==SELECIONAR_PERSONAGEM || telaAtual==CONFIRMAR_REBOOT 
					   || telaAtual==CONFIRMAR_SAIDA || telaAtual==SELECIONAR_DIFICULDADE){
		if(tecla==GLUT_KEY_UP && spriteBegin==0.5){
			spriteBegin=0;
			spriteEnd=0.5;
		}
		if(tecla==GLUT_KEY_DOWN && spriteBegin==0){
			spriteBegin+=spriteEnd;
			spriteEnd+=spriteEnd;
		}
	}
}

//teclas de suporte no jogo
void teclasJogo(unsigned char tecla,int x,int y){
	//saida com ESC
	if(tecla==ESC){
		spriteBegin=0;
		spriteEnd=(float)1/(float)2;
		telaAtual=CONFIRMAR_SAIDA;
		reinicio=1;
		setup();
		musicJOGO.stop();
		musicMENUS.play();
	}
	//cheat =D
	if(tecla && tecla!='1' && tecla!='0'){
		cheat=0;
	}
	if(tecla=='1' && cheat==2){
		cheat++;
	}
	if(tecla=='0' && (cheat==3 || cheat==4)){
		if(cheat==4)
			musicCheat.play();
		cheat++;
	}
	switch(telaAtual){
		case MENU:
			if(tecla==ENTER && spriteBegin==0){
				spriteEnd=(float)1/(float)2;
				spriteBegin=0;
				telaAtual=SELECIONAR_PERSONAGEM;
			}
			if(tecla==ENTER && spriteBegin==0.5){
				spriteEnd=1;
				spriteBegin=0;
				telaAtual=COMO_JOGAR;
			}
			break;
		case JOGO:
			if(tecla=='p' || tecla=='P'){ 
				if(pause==0){
					pause=1;
					telaAtual=PAUSE;
					musicJOGO.pause();
				}
			}
				
			if(tecla=='r' || tecla=='R'){
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=CONFIRMAR_REBOOT;
				musicJOGO.pause();
				pause=1;
				reinicio=1;
			}
			break;

		case COMO_JOGAR:
			if(tecla=='m'){
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=MENU;
			}

		case SELECIONAR_PERSONAGEM:
			if(tecla==ENTER && spriteBegin==0){
				escolha_Personagem=LULA;
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=SELECIONAR_DIFICULDADE;
				
			}
			if(tecla==ENTER && spriteBegin==0.5){
				escolha_Personagem=AECIO;
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=SELECIONAR_DIFICULDADE;
				printf("%d\n",escolha_Personagem );
			}
			break;

		case SELECIONAR_DIFICULDADE:
			if(tecla==ENTER && spriteBegin==0 ){
				setup();
				pause=0;
				reinicio=0;
				tempo=0;
				vidas=3;
				telaAtual=JOGO;
				indexCair=0;
				indexCriar=0;
				devoCriar=1;
				spriteBegin=0;
				spriteEnd=1;
				tempoCriaNovoInimigo=1000;
				tempoCriaNovoInimigoTeleguiado=10000;
				telaAtual=JOGO;
				musicMENUS.stop();
				musicJOGO.play();
				
			}
			if(tecla==ENTER && spriteBegin==0.5){
				setup();
				pause=0;
				reinicio=0;
				tempo=0;
				vidas=3;
				telaAtual=JOGO;
				indexCair=0;
				indexCriar=0;
				devoCriar=1;
				spriteBegin=0;
				spriteEnd=1;
				tempoCriaNovoInimigo=700;
				tempoCriaNovoInimigoTeleguiado=5000;
				telaAtual=JOGO;
				musicMENUS.stop();
				musicJOGO.play();
			}
			setupPersonagem(&imgPersonagem,&personagem,&escolha_Personagem);
			//controle de tempo para criação
			glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
			glutTimerFunc(tempoCriaNovoInimigoTeleguiado,timerCriarInimigoTeleguiado,0);
			//timer para barra de tempo
			glutTimerFunc(1009,timerTempo,0);
			break;

		case PERDEU_VIDA:
			if(tecla==ENTER){
				telaAtual=JOGO;
				rebootParcialTirandoVida();
				musicMENUS.stop();
				musicJOGO.play();
			}
			break;

		case PAUSE:
			if(tecla=='p' || tecla=='P'){ 
				pause=0;
				telaAtual=JOGO;
				glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
				glutTimerFunc(1009,timerTempo,0);
				musicMENUS.stop();
				musicJOGO.play();
				
			}
			break;

		case GAMEOVER:
			if(tecla=='r' || tecla=='R'){
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=SELECIONAR_PERSONAGEM;
				reinicio=1;
				setup();
			}
		case VITORIA:
			if(tecla=='r' || tecla=='R'){
				spriteBegin=0;
				spriteEnd=(float)1/(float)2;
				telaAtual=SELECIONAR_PERSONAGEM;
				reinicio=1;
				setup();
			}
			break;
		case CONFIRMAR_SAIDA:
			if(tecla==ENTER && spriteBegin==0){
				exit(0);
			}
			if(tecla==ENTER && spriteBegin==0.5){
				spriteEnd=(float)1/(float)2;
				spriteBegin=0;
				telaAtual=MENU;
				reinicio=1;
				setup();
			}
			break;

		case CONFIRMAR_REBOOT:
			if(tecla==ENTER && spriteBegin==0){
				spriteEnd=(float)1/(float)2;
				spriteBegin=0;
				telaAtual=SELECIONAR_PERSONAGEM;
				musicMENUS.play();
			}
			if(tecla==ENTER && spriteBegin==0.5){
				spriteEnd=1;
				spriteBegin=0;
				pause=0;
				reinicio=0;
				telaAtual=JOGO;
				glutTimerFunc(tempoCriaNovoInimigo, timerCriar, 0);
				glutTimerFunc(1009,timerTempo,0);
				musicMENUS.stop();
				musicJOGO.play();
			}
			break;
	}
	glutPostRedisplay();
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
	//glutMouseFunc(mouseMenu);
	glutKeyboardFunc(teclasJogo);
	glutSpecialFunc(teclasEspeciais);
	glutIdleFunc(fazCair);
	

	glutMainLoop();
	return 0;
}