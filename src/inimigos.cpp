#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "inimigos.h"
#include "personagem.h"
using namespace std;

/*...............................
**ARQUIVO DE FUNÇÕES DO INIMIGO** 
...............................*/

//desenha novo inimigo
void desenhaQuadradoInimigo(Inimigo *inimigo, int *controleCair,int *indexCair,int indexCriar,int *lado,int *imgJapaPF,int *imgJuizMoro){
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	if(inimigo[indexCriar].tipo==JapaPF){
		glBindTexture(GL_TEXTURE_2D, *imgJapaPF);
		glPushMatrix();
			glTranslatef(inimigo[indexCriar].x , inimigo[indexCriar].y, 0);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(0,0);
				glTexCoord2f(1, 0);	glVertex2f(*lado,0);
	  			glTexCoord2f(1, 1); glVertex2f(*lado,*lado);
	  			glTexCoord2f(0, 1);	glVertex2f(0,*lado);			
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();
	}
	else{
		glBindTexture(GL_TEXTURE_2D, *imgJuizMoro);
		glPushMatrix();
			glTranslatef(inimigo[indexCriar].x , inimigo[indexCriar].y, 0);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(0,0);
				glTexCoord2f(1, 0);	glVertex2f(*lado,0);
	  			glTexCoord2f(1, 1); glVertex2f(*lado,*lado);
	  			glTexCoord2f(0, 1);	glVertex2f(0,*lado);			
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();
	}
	controleCair[*indexCair]=indexCriar;
	*indexCair=indexCriar+1;
}

//desenha o movimento de queda
void desenhaCairInimigo(Inimigo *inimigo,int *controleCair,int *indexCair,int *lado,int *imgJapaPF,int *imgJuizMoro){
	GLint i;
	for(i=0;i<*indexCair;i++){
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		if(inimigo[controleCair[i]].tipo==JapaPF){
			glBindTexture(GL_TEXTURE_2D, *imgJapaPF);
			glPushMatrix();
				glTranslatef(inimigo[controleCair[i]].x , inimigo[controleCair[i]].y, 0);
				glBegin(GL_POLYGON);
					glTexCoord2f(0, 0); glVertex2f(0,0);
					glTexCoord2f(1, 0);	glVertex2f(*lado,0);
					glTexCoord2f(1, 1); glVertex2f(*lado,*lado);
					glTexCoord2f(0, 1);	glVertex2f(0,*lado);			
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			glPopMatrix();
		}
		else{
			glBindTexture(GL_TEXTURE_2D, *imgJuizMoro);
			glPushMatrix();
				glTranslatef(inimigo[controleCair[i]].x , inimigo[controleCair[i]].y, 0);
				glBegin(GL_POLYGON);
					glTexCoord2f(0, 0); glVertex2f(0,0);
					glTexCoord2f(1, 0);	glVertex2f(*lado,0);
					glTexCoord2f(1, 1); glVertex2f(*lado,*lado);
					glTexCoord2f(0, 1);	glVertex2f(0,*lado);			
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			glPopMatrix();	
		}
	}
}

//inicializa inimigos de maneira aleatoria
void setupInimigo(Inimigo *inimigo, int *imgJapaPF,int *imgJuizMoro){
	GLint i;
	for(i=0;i<1000;i++){
		inimigo[i].x=(rand()%650)-350;
		inimigo[i].y=200;
		inimigo[i].tipo=JapaPF;
	}
	*imgJuizMoro = SOIL_load_OGL_texture(
	    "img/moro.jpg",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (*imgJuizMoro == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
	*imgJapaPF = SOIL_load_OGL_texture(
	    "img/japa.png",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_INVERT_Y
 	);
 	if (imgJapaPF == 0 ) {
    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  	}
}

void cairInimigo(int *indexCair,Inimigo *inimigo,int *controleCair,float *velocidade,int i){
	inimigo[controleCair[i]].y=inimigo[controleCair[i]].y-(*velocidade);
}
