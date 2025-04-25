#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>


typedef struct
{
	SDL_Surface * bg_smenu_joueur;

	SDL_Surface * mono_btn[2];
	SDL_Surface * multi_btn[2];
	SDL_Surface * retour_btn[2];
	SDL_Surface * input1_btn[2];
	SDL_Surface * input2_btn[2];
	SDL_Surface * avatar1_btn[2];
	SDL_Surface * avatar2_btn[2];
	SDL_Surface * valider_btn[2];

	SDL_Rect pos_btn_mono;
	SDL_Rect pos_btn_multi;
	SDL_Rect pos_btn_retour;
	SDL_Rect pos_btn_input1;
	SDL_Rect pos_btn_input2;
	SDL_Rect pos_btn_avatar1;
	SDL_Rect pos_btn_avatar2;
	SDL_Rect pos_btn_valider;

	int etat_btn_mono;//0:btn non selectionner 1:btn selectionner
	int etat_btn_multi;
	int etat_btn_avatar1; 
	int etat_btn_avatar2;
	int etat_btn_input1;
	int etat_btn_input2;
	int etat_btn_retour;
	int etat_btn_valider;

	int selecter_btn_avatar1;
	int selecter_btn_avatar2;
	int selecter_btn_input1;
	int selecter_btn_input2;

	int num_page_joueur;//0:mono,multi 1:avatar,input

	int mode_jeux;//0:mono 1:multi

	Mix_Music *background_music;
	Mix_Chunk *son_btn_selectionner;
}Menu;

void init_menu_joueur(Menu *m,SDL_Surface *ecran);
int collision_avec_souris(SDL_Rect  pos_btn);
void afficher_menu_joueur(Menu m,SDL_Surface *ecran);
void gerer_event_menu_joueur(Menu *m,SDL_Event event, int *quitter,int *indice_ecran);
void miseajour_menu_joueur(Menu *m);


#endif
