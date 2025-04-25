prog:main.o menu.o joueur.o
	gcc main.o menu.o joueur.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o:main.c
	gcc -c main.c -o main.o -g
menu.o:menu.c
	gcc -c menu.c -o menu.o -g
joueur.o:joueur.c
	gcc -c joueur.c -o joueur.o -g
