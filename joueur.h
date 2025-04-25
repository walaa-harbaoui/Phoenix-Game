#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct{
	int right;
	int left;
	int jump;
	int attack;
	int acceleration;
	int defense;
}Input;

typedef struct{
	int num_avatar;
	SDL_Surface *img_left;
	SDL_Surface *img_right;

	SDL_Rect pos_ecran;
	SDL_Rect pos_affichage;

	Input input;
	int etat_right;
	int etat_left;
	int etat_jump;
	int etat_attack;
	int etat_acceleration;
	int etat_defense;

	float vitesse;
	float acceleration;
	int direction; 
	int derniere_direction; 
	int compteur_animation;

	int en_saut; 
	int en_chute; 
	float vitesse_y;
	float gravite; 
	int pos_sol;

	int score;
	SDL_Surface* score_surface;
	SDL_Rect pos_score;

	int vies;
	SDL_Surface *coeurs;
	SDL_Rect pos_coeurs;
}Joueur;


void init_joueur(Joueur *j,int avatar,int input,SDL_Surface *ecran);
void afficher_joueur(Joueur j,SDL_Surface *ecran);
void gerer_event_joueur(Joueur *j,SDL_Event event);
void deplacer_joueur(Joueur *j);
void animer_joueur(Joueur *j,int avatar);
void saut_joueur(Joueur *j);
void gestion_vies_score(Joueur *j, TTF_Font *font);
#endif



