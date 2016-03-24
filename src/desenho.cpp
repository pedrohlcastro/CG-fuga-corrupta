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
****ARQUIVO DE FUNÇÕES DE DESENHO 
****DE ELEMENTOS DO GAME*********
...............................*/


void setupDesenho(int *imgFundo,int *imgVidas,int *imgMenu,int *imgComoJogar,int *imgSelecaoPersonagem,
					int *imgConfirmaPersonagem,int *imgPause,int *imgPerdeuVida,int *imgPerdeuJogo,int *imgGanhouJogo,int *imgConfirmaSaida,int *imgConfirmaReboot){
	*imgFundo = SOIL_load_OGL_texture(
	    "img/tela_fundo.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgFundo == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgVidas = SOIL_load_OGL_texture(
	    "img/coracao.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgVidas == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}

  	*imgMenu = SOIL_load_OGL_texture(
	    "img/menu.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgMenu == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgComoJogar = SOIL_load_OGL_texture(
	    "img/como_jogar.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgComoJogar == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgSelecaoPersonagem = SOIL_load_OGL_texture(
	    "img/personagem.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgSelecaoPersonagem == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgConfirmaPersonagem = SOIL_load_OGL_texture(
	    "img/confirma_personagem.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgConfirmaPersonagem == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgPause = SOIL_load_OGL_texture(
	    "img/pause.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgPause == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgPerdeuVida = SOIL_load_OGL_texture(
	    "img/perdeu_vida.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgPerdeuVida == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgPerdeuJogo = SOIL_load_OGL_texture(
	    "img/fim_jogo.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgPerdeuJogo == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgGanhouJogo = SOIL_load_OGL_texture(
	    "img/venceu.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgGanhouJogo == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgConfirmaSaida = SOIL_load_OGL_texture(
	    "img/confirma_saida.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgConfirmaSaida == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
  	*imgConfirmaReboot = SOIL_load_OGL_texture(
	    "img/reinicio.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgConfirmaReboot == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
}
void desenhaVidas(int *vidas,int *imgVidas){
	GLint i,posicao_xVidas=-50;
	for(i=0;i<*vidas;i++){
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, *imgVidas);
		glPushMatrix();
			glTranslatef(posicao_xVidas ,280 ,0);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(0,0);
				glTexCoord2f(1, 0);	glVertex2f(50,0);
	  			glTexCoord2f(1, 1); glVertex2f(50,50);
	  			glTexCoord2f(0, 1);	glVertex2f(0,50);			
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();
		posicao_xVidas+=50;
	}
}

void desenhaFundo(int *imgFundo,float *spriteBegin,float *spriteEnd){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *imgFundo);
	glPushMatrix();
		glTranslatef(-350 ,-350 ,0);
		glBegin(GL_POLYGON);
			glTexCoord2f(*spriteBegin, 0); 						glVertex2f(0,0);
			glTexCoord2f(*spriteEnd, 0);				glVertex2f(700,0);
  			glTexCoord2f(*spriteEnd, 1); 				glVertex2f(700,700);
  			glTexCoord2f(*spriteBegin, 1);							glVertex2f(0,700);			
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenhaTempo(int *tempo){
	GLint i,aux=-350;
	GLint topo_da_tela=325;
	//cor azul bandeira brasil
	glColor3f(0.0859375,0.31640625,0.71875);
	for(i=0;i<*tempo;i++){
		glPushMatrix();
			glTranslatef(aux , topo_da_tela, 0);
			glBegin(GL_POLYGON);
				glVertex2f(0,0);
				glVertex2f(10,0);
				glVertex2f(10,30);
				glVertex2f(0,30);			
			glEnd();
		glPopMatrix();
		aux+=10;
	}
}

