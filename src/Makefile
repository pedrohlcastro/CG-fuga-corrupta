CC=g++
all:arquivos

arquivos: main.o inimigos.o desenho.o personagem.o
	$(CC) main.o inimigos.o desenho.o personagem.o -o executavel -Lincludes -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm
	@echo "\nCRIADO COM SUCESSO UTILIZE MAKE RUN PARA RODAR\n"

main.o: main.cpp
	$(CC) -o main.o -c main.cpp -Lincludes -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm

inimigos.o: inimigos.cpp
	$(CC) -o inimigos.o -c inimigos.cpp -Lincludes -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm

desenho.o: desenho.cpp
	$(CC) -o desenho.o -c desenho.cpp -Lincludes -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm

personagem.o: personagem.cpp
	$(CC) -o personagem.o -c personagem.cpp -Lincludes -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm
	
run:
	./executavel

clean:
	rm -rf *o arquivos
	@echo "Arquivos .o deletados com suecesso\n"

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsfml-dev
	sudo apt-get install libsoil-dev
