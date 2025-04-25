#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "menu.h"
#include "joueur.h"

int main (int argc, char *argv[] )
{
	int quitter=0;
	int indice_ecran=0; 
	SDL_Event event;
	SDL_Surface * background=NULL;
	SDL_Surface *ecran;
	TTF_Font *font;
	Menu menu;
	Joueur *joueurs=NULL;
	int nb_joueur=1;
	int avatar[2];
	int input[2];
	int i;
	Uint32 dt,t_prev;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
			return 1;

		}
	
	ecran=SDL_SetVideoMode(1792,920,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

	background=IMG_Load("background.jpeg"); 
	if (!background) {
	    printf("Erreur chargement background : %s\n", IMG_GetError());
	    return 1;
	}	
	
	if (ecran==NULL )
	{
		printf("Echec de creation de la fenetre: %s.\n", SDL_GetError());
		return 1;
	}
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);

	TTF_Init();
	font = TTF_OpenFont("arial.ttf",30);
	if (!font) {
		printf("Erreur chargement police : %s\n", TTF_GetError());
		return 1;
    	}

	init_menu_joueur(&menu,ecran);
	

	while(quitter==0)
	{
		t_prev=SDL_GetTicks();
		switch(indice_ecran)
		{
		case 0:
			
			afficher_menu_joueur(menu,ecran);
			SDL_Flip(ecran);

			
			gerer_event_menu_joueur(&menu,event,&quitter,&indice_ecran);

			
			miseajour_menu_joueur(&menu);

			if(indice_ecran==1){
				if(menu.mode_jeux==0)
					nb_joueur=1;
				else
					nb_joueur=2;

				if(menu.selecter_btn_avatar1==1){
					avatar[0]=1;
					avatar[1]=2;}
				else{
					avatar[0]=2;
					avatar[1]=1;}

				if(menu.selecter_btn_input1==1){
					input[0]=1;
					input[1]=2;}
				else{
					input[0]=2;
					input[1]=1;}


				joueurs=malloc(nb_joueur*sizeof(Joueur));

				for(i=0;i<nb_joueur;i++){
					init_joueur(&joueurs[i],avatar[i],input[i],ecran);}
			}

			
			break;
		case 1:
				
			SDL_BlitSurface(background,NULL,ecran,NULL);
			for(i=0;i<nb_joueur;i++){
				gestion_vies_score(&joueurs[i],font);
				afficher_joueur(joueurs[i],ecran);}
			SDL_Flip(ecran);

			
			while(SDL_PollEvent(&event)){
				switch(event.type){
					case SDL_QUIT:
						quitter=1;
						break;
				}
				for(i=0;i<nb_joueur;i++){
					gerer_event_joueur(&joueurs[i],event);}
			}
			
			for(i=0;i<nb_joueur;i++){
					deplacer_joueur(&joueurs[i]);
					saut_joueur(&joueurs[i]);}

			for(i=0;i<nb_joueur;i++){
				animer_joueur(&joueurs[i],avatar[i]);}

			if(dt<16){
				SDL_Delay(16-dt);
				dt=16;}

			break;
		}
		dt=SDL_GetTicks()-t_prev;
	}
	
	for (i=0;i<nb_joueur;i++) {
		if (joueurs[i].score_surface) 
			SDL_FreeSurface(joueurs[i].score_surface);
		if (joueurs[i].coeurs) 
			SDL_FreeSurface(joueurs[i].coeurs);}
	free(joueurs);
	TTF_CloseFont(font);
	Mix_FreeChunk(menu.son_btn_selectionner);
	Mix_FreeMusic(menu.background_music);
	Mix_CloseAudio();
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(background);
	SDL_Quit();

	
	return 0;
}



