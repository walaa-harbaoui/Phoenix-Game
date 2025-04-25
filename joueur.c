#include "joueur.h"

void init_joueur(Joueur *j,int avatar,int input,SDL_Surface *ecran)
{
	int w_joueur;
	int h_joueur;

	j->num_avatar=avatar;
	if(avatar==1){
		j->img_left=IMG_Load("avatar1left.png");
		j->img_right=IMG_Load("avatar1right.png");}
	else{
		j->img_left=IMG_Load("avatar2left.png");
		j->img_right=IMG_Load("avatar2right.png");}
	if(j->img_left == NULL || j->img_right == NULL) {
		printf("erreur: impossible de charger les images du joueur\n");}

	if(j->num_avatar==1){
		w_joueur=210;
		h_joueur=310;}
	else{
		w_joueur=170;
		h_joueur=350;}

	j->pos_ecran.x=0;
	j->pos_ecran.y=850-h_joueur; 
	j->pos_ecran.w=w_joueur;
	j->pos_ecran.h=h_joueur;

	j->pos_affichage.x=0;
	j->pos_affichage.y=0;
	j->pos_affichage.w=w_joueur;
	j->pos_affichage.h=h_joueur;

	if(input==1){
		j->input.right=SDLK_RIGHT;
		j->input.left=SDLK_LEFT;
		j->input.jump=SDLK_UP;
		j->input.attack=SDLK_m;
		j->input.defense=SDLK_j;
		j->input.acceleration=SDLK_l;}
	else{
		j->input.right=SDLK_d;
		j->input.left=SDLK_q;
		j->input.jump=SDLK_z;
		j->input.attack=SDLK_c;
		j->input.defense=SDLK_s;
		j->input.acceleration=SDLK_x;}		

	j->etat_right=0;
	j->etat_left=0;
	j->etat_jump=0;
	j->etat_attack=0;
	j->etat_defense=0;
	j->etat_acceleration=0;

	j->vitesse=0;
	j->acceleration=0;
	j->direction=0;
	j->derniere_direction=0;

	j->compteur_animation=0;

	j->en_saut=0; 
	j->en_chute=0;
	 
	j->vitesse_y=-20;
	j->gravite=0.5; 
	j->pos_sol=850-h_joueur;

	
	if(avatar==1){
		j->coeurs=IMG_Load("full.png");
		j->pos_coeurs.x=40; 
	} else {
		j->coeurs=IMG_Load("full.png");
		j->pos_coeurs.x=1300; 
	}
	j->pos_coeurs.y=20;
	j->vies = 3; 

	
	j->score=0;
	j->score_surface=NULL;
	if(avatar==1)
		j->pos_score.x=335;
	else
		j->pos_score.x=1580;
	j->pos_score.y=40;

}

void afficher_joueur(Joueur j,SDL_Surface *ecran)
{
	if(j.derniere_direction==1)
		SDL_BlitSurface(j.img_right,&j.pos_affichage,ecran,&j.pos_ecran);
	else if(j.derniere_direction==-1)
		SDL_BlitSurface(j.img_left,&j.pos_affichage,ecran,&j.pos_ecran);
	else
		SDL_BlitSurface(j.img_right,&j.pos_affichage,ecran,&j.pos_ecran);
	
	if (j.coeurs) 
        	SDL_BlitSurface(j.coeurs, NULL, ecran, &j.pos_coeurs);
	
	if(j.score_surface)
		SDL_BlitSurface(j.score_surface, NULL, ecran, &j.pos_score);
}

void gerer_event_joueur(Joueur *j,SDL_Event event)
{
	switch(event.type){
		case SDL_KEYDOWN:
			if(event.key.keysym.sym==j->input.right){
				j->etat_right=1;
				j->direction=1;
				j->derniere_direction=1;}
			if(event.key.keysym.sym==j->input.left){
				j->etat_left=1;
				j->direction=-1;
				j->derniere_direction=-1;}
			if(event.key.keysym.sym==j->input.attack)
				j->etat_attack=1;
			if(event.key.keysym.sym==j->input.jump)
				j->etat_jump=1;
			if(event.key.keysym.sym==j->input.defense)
				j->etat_defense=1;
			if(event.key.keysym.sym==j->input.acceleration)
				j->etat_acceleration=1;
			break;
		case SDL_KEYUP:
			if(event.key.keysym.sym==j->input.right){
				j->etat_right=0;
				j->derniere_direction=1;}
			if(event.key.keysym.sym==j->input.left){
				j->etat_left=0;
				j->derniere_direction=-1;}
			if(event.key.keysym.sym==j->input.jump)
				j->etat_jump=0;
			if(event.key.keysym.sym==j->input.jump)
				j->etat_jump=0;
			if(event.key.keysym.sym==j->input.defense)
				j->etat_defense=0;
			if(event.key.keysym.sym==j->input.acceleration)
				j->etat_acceleration=0;
			break;
	}
}

void deplacer_joueur(Joueur *j)
{
	float vitesse_total;
	if(j->etat_left==0 && j->etat_right==0){
		j->vitesse-=0.15;
		if(j->vitesse<0)
			j->vitesse=0;}
	else{
		j->vitesse+=0.15;
		if(j->vitesse>2)
			j->vitesse=2;}

	if(j->etat_acceleration==1){
		j->acceleration+=0.2;
		if(j->acceleration>3)
			j->acceleration=3;}
	else{
		j->acceleration-=0.15;
		if(j->acceleration<0)
			j->acceleration=0;}
		
	if(j->vitesse==0)
		j->direction=0;

	vitesse_total=j->acceleration+j->vitesse;

	j->pos_ecran.x+=vitesse_total*j->direction;

}

void animer_joueur(Joueur *j,int avatar)
{
	j->compteur_animation++;
	if(avatar==1){
		if(j->en_saut==0 && j->en_chute==0){
			if(j->etat_attack==0){
				
				if(j->direction==0  && j->derniere_direction==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=0){
						j->pos_affichage.x=0;
						j->pos_affichage.y=0;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>2580)
						j->pos_affichage.x=0;

				}
				else if(j->direction==0  && j->derniere_direction==-1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=0){
						j->pos_affichage.x=2675;
						j->pos_affichage.y=0;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<2675-(430*6))
						j->pos_affichage.x=2675;

				}
				
				if(j->direction==1 && j->etat_acceleration==0 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=595){
						j->pos_affichage.x=0;
						j->pos_affichage.y=595;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>2580) 
						j->pos_affichage.x=0;
				}
				else if(j->direction==-1 && j->etat_acceleration==0 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=595){
						j->pos_affichage.x=2675;
						j->pos_affichage.y=595;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<95) 
						j->pos_affichage.x=2675;

				}
				
				if(j->direction==1 && j->etat_acceleration==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1200){
						j->pos_affichage.x=0;
						j->pos_affichage.y=1200;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>430*6) 
						j->pos_affichage.x=0;
				}
				else if(j->direction==-1 && j->etat_acceleration==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1200){
						j->pos_affichage.x=2675;
						j->pos_affichage.y=1200;
						j->pos_affichage.w=210;
						j->pos_affichage.h=310;}

					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<(2675-(430*6))) 
						j->pos_affichage.x=2675;

				}
			}else{
				
				if(j->derniere_direction==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1797){
						j->pos_affichage.x=0;
						j->pos_affichage.y=1797;
						j->pos_affichage.w=360;
						j->pos_affichage.h=460;}

					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>2525){ 
						j->pos_affichage.x=0;
						j->etat_attack=0;}
				}
				else if(j->derniere_direction==-1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1797){
						j->pos_affichage.x=2525;
						j->pos_affichage.y=1797;
						j->pos_affichage.w=360;
						j->pos_affichage.h=460;}

					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<(2525-(430*6))){ 
						j->pos_affichage.x=2525;
						j->etat_attack=0;}
				}
			}
		}else{
			
			if(j->derniere_direction==1 && j->compteur_animation%15==0){
				if(j->pos_affichage.y!=2390){
					j->pos_affichage.x=0;
					j->pos_affichage.y=2390;
					j->pos_affichage.w=280;
					j->pos_affichage.h=400;}

				if(j->en_saut==1){
					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>(430*3))
						j->pos_affichage.x=430*3;
				}else if(j->en_chute==1){
					j->pos_affichage.x+=430; 
					if(j->pos_affichage.x>2580)
						j->pos_affichage.x=2580;}

			}
			else if(j->derniere_direction==-1 && j->compteur_animation%15==0){
				if(j->pos_affichage.y!=2390){
					j->pos_affichage.x=2605;
					j->pos_affichage.y=2390;
					j->pos_affichage.w=280;
					j->pos_affichage.h=400;}

				if(j->en_saut==1){
					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<(2605-(430*3)))
						j->pos_affichage.x=2605-(430*3);
				}else if(j->en_chute==1){
					j->pos_affichage.x-=430; 
					if(j->pos_affichage.x<(2605-(430*6)))
						j->pos_affichage.x=2605-(430*6);}

			}


		}
	}else{
		if(j->en_saut==0 && j->en_chute==0){
			if(j->etat_attack==0){
				
				if(j->direction==0  && j->derniere_direction==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=0){
						j->pos_affichage.x=0;
						j->pos_affichage.y=0;
						j->pos_affichage.w=170;
						j->pos_affichage.h=350;}

					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>3090)
						j->pos_affichage.x=0;

				}
				else if(j->direction==0  && j->derniere_direction==-1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=0){
						j->pos_affichage.x=4870;
						j->pos_affichage.y=0;
						j->pos_affichage.w=170;
						j->pos_affichage.h=365;}

					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<1781)
						j->pos_affichage.x=2675;

				}
				
				if(j->direction==1 && j->etat_acceleration==0 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=645){
						j->pos_affichage.x=0;
						j->pos_affichage.y=645;
						j->pos_affichage.w=170;
						j->pos_affichage.h=365;}

					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>3090) 
						j->pos_affichage.x=0;
				}
				else if(j->direction==-1 && j->etat_acceleration==0 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=645){
						j->pos_affichage.x=4870;
						j->pos_affichage.y=64;
						j->pos_affichage.w=170;
						j->pos_affichage.h=365;}

					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<1780) 
						j->pos_affichage.x=4870;

				}
				
				if(j->direction==1 && j->etat_acceleration==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1275){
						j->pos_affichage.x=0;
						j->pos_affichage.y=1275;
						j->pos_affichage.w=170;
						j->pos_affichage.h=365;}

					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>515*6) 
						j->pos_affichage.x=0;
				}
				else if(j->direction==-1 && j->etat_acceleration==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1275){
						j->pos_affichage.x=4870;
						j->pos_affichage.y=1275;
						j->pos_affichage.w=170;
						j->pos_affichage.h=365;}

					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<(4870-(515*6))) 
						j->pos_affichage.x=4870;

				}
			}else{
				
				if(j->derniere_direction==1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1930){
						j->pos_affichage.x=0;
						j->pos_affichage.y=1930;
						j->pos_affichage.w=430;
						j->pos_affichage.h=465;}

					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>4611){ 
						j->pos_affichage.x=0;
						j->etat_attack=0;}
				}
				else if(j->derniere_direction==-1 && j->compteur_animation%15==0){
					if(j->pos_affichage.y!=1930){
						j->pos_affichage.x=4611;
						j->pos_affichage.y=1930;
						j->pos_affichage.w=430;
						j->pos_affichage.h=465;}

					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<(4611-(515*6))){ 
						j->pos_affichage.x=4611;
						j->etat_attack=0;}
				}
			}
		}else{
			
			if(j->derniere_direction==1 && j->compteur_animation%15==0){
				if(j->pos_affichage.y!=2575){
					j->pos_affichage.x=0;
					j->pos_affichage.y=2575;
					j->pos_affichage.w=195;
					j->pos_affichage.h=390;}

				if(j->en_saut==1){
					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>(515*3))
						j->pos_affichage.x=515*3;
				}else if(j->en_chute==1){
					j->pos_affichage.x+=515; 
					if(j->pos_affichage.x>3090)
						j->pos_affichage.x=0;}

			}
			else if(j->derniere_direction==-1 && j->compteur_animation%15==0){
				if(j->pos_affichage.y!=2575){
					j->pos_affichage.x=4846;
					j->pos_affichage.y=2575;
					j->pos_affichage.w=195;
					j->pos_affichage.h=390;}

				if(j->en_saut==1){
					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<(4846-(515*3)))
						j->pos_affichage.x=4846-(515*3);
				}else if(j->en_chute==1){
					j->pos_affichage.x-=515; 
					if(j->pos_affichage.x<(4846-(515*6)))
						j->pos_affichage.x=4846-(515*6);}

			}


		}	
	}
	if(j->compteur_animation>10000)
		 j->compteur_animation=0;
}

void saut_joueur(Joueur *j)
{
	
	if(j->etat_jump==1 && j->en_saut==0 && j->en_chute==0){
		j->en_saut=1;
		j->vitesse_y=-20;
		j->etat_jump==0;}

	
	if(j->en_saut==1 || j->en_chute==1){
		j->vitesse_y+=j->gravite; 
		j->pos_ecran.y+=(int)j->vitesse_y;

		if(j->vitesse_y>=0 && j->en_saut==1){
			j->en_saut=0;
			j->en_chute=1;}

		if(j->pos_ecran.y>=j->pos_sol){
			j->pos_ecran.y=j->pos_sol; 
			j->vitesse_y=0;
			j->en_saut=0;
			j->en_chute=0;}
	}
}

void gestion_vies_score(Joueur *j, TTF_Font *font)
{
	char score_text[32];
	snprintf(score_text, sizeof(score_text), "Score: %d", j->score);

	
	if(j->score_surface)
		SDL_FreeSurface(j->score_surface);
	SDL_Color white = {255, 255, 255};
	j->score_surface = TTF_RenderText_Solid(font, score_text, white);

	
	if(j->vies==3)
		j->coeurs=IMG_Load("full.png");
	else if(j->vies==2)
		j->coeurs=IMG_Load("2HP.png");
	else if(j->vies==1)
		j->coeurs=IMG_Load("1HP.png");
	else if(j->vies==0)
		j->coeurs=IMG_Load("0HP.png");
    
}




