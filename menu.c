#include "menu.h"


void init_menu_joueur(Menu *m,SDL_Surface *ecran)
{
	m->bg_smenu_joueur=IMG_Load("background.png"); 
	if(m->bg_smenu_joueur==NULL)
	{
		printf("error load background \n");
	}
	m->mono_btn[0]=IMG_Load("mono1.jpeg");
	m->mono_btn[1]=IMG_Load("mono2.jpeg");

	m->multi_btn[0]=IMG_Load("multi1.jpeg");
	m->multi_btn[1]=IMG_Load("multi2.jpeg");

	m->retour_btn[0]=IMG_Load("retour1.jpeg");
	m->retour_btn[1]=IMG_Load("retour2.jpeg");

	m->input1_btn[0]=IMG_Load("input11.jpeg");
	m->input1_btn[1]=IMG_Load("input12.jpeg");

	m->input2_btn[0]=IMG_Load("input21.jpeg");
	m->input2_btn[1]=IMG_Load("input22.jpeg");

	m->avatar1_btn[0]=IMG_Load("avatar11.jpeg");
	m->avatar1_btn[1]=IMG_Load("avatar12.jpeg");

	m->avatar2_btn[0]=IMG_Load("avatar21.jpeg");
	m->avatar2_btn[1]=IMG_Load("avatar22.jpeg");

	m->valider_btn[0]=IMG_Load("valider1.jpeg");
	m->valider_btn[1]=IMG_Load("valider2.jpeg");


	m->pos_btn_mono.x = (ecran->w/4) - (m->mono_btn[0]->w/2);
	m->pos_btn_mono.y = (ecran->h/2) - (m->mono_btn[0]->h/2);
	m->pos_btn_mono.w = m->mono_btn[0]->w;
	m->pos_btn_mono.h = m->mono_btn[0]->h;

	m->pos_btn_multi.x = ((ecran->w*3)/4) - (m->multi_btn[0]->w/2);
	m->pos_btn_multi.y = (ecran->h/2) - (m->multi_btn[0]->h/2);
	m->pos_btn_multi.w = m->multi_btn[0]->w;
	m->pos_btn_multi.h = m->multi_btn[0]->h;

	m->pos_btn_retour.x = ecran->w - m->retour_btn[0]->w - 50;
	m->pos_btn_retour.y = ecran->h - m->retour_btn[0]->h - 50;
	m->pos_btn_retour.w = m->retour_btn[0]->w;
	m->pos_btn_retour.h = m->retour_btn[0]->h;

	m->pos_btn_avatar1.x = (ecran->w/4) - (m->avatar1_btn[0]->w/2);
	m->pos_btn_avatar1.y = (ecran->h/3);
	m->pos_btn_avatar1.w = m->avatar1_btn[0]->w;
	m->pos_btn_avatar1.h = m->avatar1_btn[0]->h;
	
	m->pos_btn_avatar2.x = ((ecran->w*3)/4) - (m->avatar2_btn[0]->w/2);
	m->pos_btn_avatar2.y = (ecran->h/3);
	m->pos_btn_avatar2.w = m->avatar2_btn[0]->w;
	m->pos_btn_avatar2.h = m->avatar2_btn[0]->h;

	m->pos_btn_input1.x = (ecran->w/4) - (m->input1_btn[0]->w/2);
	m->pos_btn_input1.y = (ecran->h*2)/3;
	m->pos_btn_input1.w = m->input1_btn[0]->w;
	m->pos_btn_input1.h = m->input1_btn[0]->h;

	m->pos_btn_input2.x = ((ecran->w*3)/4) - (m->input2_btn[0]->w/2);
	m->pos_btn_input2.y = (ecran->h*2)/3;
	m->pos_btn_input2.w = m->input2_btn[0]->w;
	m->pos_btn_input2.h = m->input2_btn[0]->h;

	m->pos_btn_valider.x = (ecran->w - m->valider_btn[0]->w)/2;
	m->pos_btn_valider.y = (ecran->h*3)/4;
	m->pos_btn_valider.w = m->valider_btn[0]->w;
	m->pos_btn_valider.h = m->valider_btn[0]->h;

	m->etat_btn_mono=0;
	m->etat_btn_multi=0;
	m->etat_btn_avatar1=0;
	m->etat_btn_avatar2=0;
	m->etat_btn_input1=0;
	m->etat_btn_input2=0;
	m->etat_btn_retour=0;
	m->etat_btn_valider=0;

	m->num_page_joueur=0;
	m->mode_jeux=0;

	m->selecter_btn_avatar1=0;
	m->selecter_btn_avatar2=0;
	m->selecter_btn_input1=0;
	m->selecter_btn_input2=0;


	m->background_music=Mix_LoadMUS("music.mp3");
	if(m->background_music==NULL){
		printf("error load music background \n");
	}
	else{
		Mix_PlayMusic(m->background_music,-1);
	}

	

	m->son_btn_selectionner=Mix_LoadWAV("click.wav");
	if(m->son_btn_selectionner==NULL){
		printf("error load hover sound \n");
	}
}

int collision_avec_souris(SDL_Rect pos_btn)
{
	int x_souris,y_souris;
	SDL_GetMouseState(&x_souris,&y_souris);
	if((x_souris > pos_btn.x) && x_souris < (pos_btn.x + pos_btn.w) && (y_souris >  pos_btn.y) && y_souris < (pos_btn.y + pos_btn.h))
		return 1;
	else
		return 0;
}

void afficher_menu_joueur(Menu m,SDL_Surface *ecran)
{
	SDL_BlitSurface(m.bg_smenu_joueur,NULL,ecran,NULL);

	if(m.num_page_joueur==0){//page mono,multi
		
		SDL_BlitSurface(m.mono_btn[m.etat_btn_mono],NULL,ecran,&m.pos_btn_mono);
		SDL_BlitSurface(m.multi_btn[m.etat_btn_multi],NULL,ecran,&m.pos_btn_multi);
		SDL_BlitSurface(m.retour_btn[m.etat_btn_retour],NULL,ecran,&m.pos_btn_retour);
	}
	else if(m.num_page_joueur==1){//page avatar,input

		SDL_BlitSurface(m.avatar1_btn[m.selecter_btn_avatar1], NULL, ecran, &m.pos_btn_avatar1);
		SDL_BlitSurface(m.avatar2_btn[m.selecter_btn_avatar2], NULL, ecran, &m.pos_btn_avatar2);
		SDL_BlitSurface(m.input1_btn[m.selecter_btn_input1], NULL, ecran, &m.pos_btn_input1);
		SDL_BlitSurface(m.input2_btn[m.selecter_btn_input2], NULL, ecran, &m.pos_btn_input2);
		SDL_BlitSurface(m.valider_btn[m.etat_btn_valider], NULL, ecran, &m.pos_btn_valider);
		SDL_BlitSurface(m.retour_btn[m.etat_btn_retour], NULL, ecran, &m.pos_btn_retour);
	}
}

void gerer_event_menu_joueur(Menu *m,SDL_Event event, int *quitter,int *indice_ecran)
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			*quitter=1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button==SDL_BUTTON_LEFT){
				if(m->etat_btn_retour==1 && m->num_page_joueur==0)//retour au menu principal
					*quitter=1;
				else if(m->etat_btn_retour==1 && m->num_page_joueur==1)
					m->num_page_joueur=0 ;

				if(m->etat_btn_mono==1){  
					m->num_page_joueur=1;
					m->etat_btn_mono=0;
					m->mode_jeux=0;}
				else if (m->etat_btn_multi==1){
					m->num_page_joueur=1;
					m->etat_btn_multi=0;
					m->mode_jeux=1;}

				if(collision_avec_souris(m->pos_btn_avatar1)==1){
					m->selecter_btn_avatar1=1;
					m->selecter_btn_avatar2=0;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_avatar2)==1){
					m->selecter_btn_avatar1=0;
					m->selecter_btn_avatar2=1;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_input1)==1){
					m->selecter_btn_input1=1;
					m->selecter_btn_input2=0;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_input2)==1){
					m->selecter_btn_input1=0;
					m->selecter_btn_input2=1;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}

				if(m->etat_btn_valider==1 && (m->selecter_btn_input1==1 || m->selecter_btn_input2==1) && (m->selecter_btn_avatar1==1 || m->selecter_btn_avatar2==1))
						*indice_ecran=1;

			}
			break;
		
		}
	}
}
				/*if(m->num_page_joueur==0){
					if(m->etat_btn_retour==1)
						*quitter=1;

					if(m->etat_btn_mono==1){ 
						m->mode_jeux=0; 
						m->num_page_joueur=1;
						m->etat_btn_mono=0;}

					else if (m->etat_btn_multi==1){
						m->mode_jeux=1;
						m->num_page_joueur=1;
						m->etat_btn_multi=0;}
				}else{
					if(m->etat_btn_retour==1)
						m->num_page_joueur==0;

					if(m->etat_btn_avatar1==1){
						m->selecter_btn_avatar1=1;
						m->selecter_btn_avatar2=0;
						Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
					else if(m->etat_btn_avatar2==1){
						m->selecter_btn_avatar1=0;
						m->selecter_btn_avatar2=1;
						Mix_PlayChannel(-1,m->son_btn_selectionner,0);}

					if(m->etat_btn_input1==1){
						m->selecter_btn_input1=1;
						m->selecter_btn_input2=0;
						Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
					else if(m->etat_btn_input2==1){
						m->selecter_btn_input1=0;
						m->selecter_btn_input2=1;
						Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
					if(m->etat_btn_valider==1 && (m->selecter_btn_input1==1 || m->selecter_btn_input2==1) && (m->selecter_btn_avatar1==1 || m->selecter_btn_avatar2==1))
						*indice_ecran=1;*/

				/*if(m->etat_btn_retour==1 && m->num_page_joueur==0)//retour au menu principal
					*quitter=1;
				else if(m->etat_btn_retour==1 && m->num_page_joueur==1)
					m->num_page_joueur=0 ;

				if(m->etat_btn_mono==1){  
					m->num_page_joueur=1;
					m->etat_btn_mono=0;
					m->mode_jeux=0;}
				else if (m->etat_btn_multi==1){
					m->num_page_joueur=1;
					m->etat_btn_multi=0;
					m->mode_jeux=1;}

				if(collision_avec_souris(m->pos_btn_avatar1)==1){
					m->etat_btn_avatar1=1;
					m->etat_btn_avatar2=0;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_avatar2)==1){
					m->etat_btn_avatar1=0;
					m->etat_btn_avatar2=1;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_input1)==1){
					m->etat_btn_input1=1;
					m->etat_btn_input2=0;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}
				else if(collision_avec_souris(m->pos_btn_input2)==1){
					m->etat_btn_input1=0;
					m->etat_btn_input2=1;
					Mix_PlayChannel(-1,m->son_btn_selectionner,0);}

				if(m->etat_btn_valider==1){//aller au sous menu meilleur score
					SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
					SDL_Flip(ecran);}*/
					
			

 
void miseajour_menu_joueur(Menu *m)
{
	if(m->num_page_joueur==0){
		if(collision_avec_souris(m->pos_btn_mono)==1){
			if(m->etat_btn_mono==0)
				Mix_PlayChannel(-1,m->son_btn_selectionner,0);
			m->etat_btn_mono=1;}
		else
			m->etat_btn_mono=0;

		if(collision_avec_souris(m->pos_btn_multi)==1){
			if(m->etat_btn_multi==0)
				Mix_PlayChannel(-1,m->son_btn_selectionner,0);
			m->etat_btn_multi=1;}
		else
			m->etat_btn_multi=0;

		if(collision_avec_souris(m->pos_btn_retour)==1){
			if(m->etat_btn_retour==0)
				Mix_PlayChannel(-1,m->son_btn_selectionner,0);
			m->etat_btn_retour=1;}
		else
			m->etat_btn_retour=0;
	}
	else{
		
		if(collision_avec_souris(m->pos_btn_valider)==1){
			if(m->etat_btn_valider==0)
				Mix_PlayChannel(-1,m->son_btn_selectionner,0);
			m->etat_btn_valider=1;}
		else
			m->etat_btn_valider=0;

		if(collision_avec_souris(m->pos_btn_retour)==1){
			if(m->etat_btn_retour==0)
				Mix_PlayChannel(-1,m->son_btn_selectionner,0);
			m->etat_btn_retour=1;}
		else
			m->etat_btn_retour=0;
		
		
	}
}


		
