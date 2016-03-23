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
ARQUIVO DE FUNÇÕES DO PERSONAGEM 
...............................*/

void setupPersonagem(int *imgPersonagem,float *y,int *escolha){
	*y=-315;
	if(*escolha==LULA){
		*imgPersonagem = SOIL_load_OGL_texture(
		    "img/lula.png",
		    SOIL_LOAD_AUTO,
		    SOIL_CREATE_NEW_ID,
		    SOIL_FLAG_INVERT_Y
	 	);
		if (*imgPersonagem == 0 ) {
	    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	  	}
	 }
	 if(*escolha==AECIO){
	 	*imgPersonagem = SOIL_load_OGL_texture(
		    "img/aecio.png",
		    SOIL_LOAD_AUTO,
		    SOIL_CREATE_NEW_ID,
		    SOIL_FLAG_INVERT_Y
	 	);
		if (*imgPersonagem == 0 ) {
	    	printf("Erro carregando textura: '%s'\n", SOIL_last_result());
	  	}
	 }
	 
}

void desenhaPersonagem(Personagem personagem,int *imgPersonagem,int *lado){
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *imgPersonagem);
	glPushMatrix();
		glTranslatef(personagem.x , personagem.y, 0);
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
