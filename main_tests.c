#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=1;
int temps_repousse_herbe=-15;

#define NB_PROIES 20
#define NB_PREDATEURS 1000


int main(void) {
  Animal *gazelle1 = creer_animal(11,9,5.7);
  Animal *gazelle2 = creer_animal(10,25,4.7);
  Animal *gazelle3 = creer_animal(0,26,5.7);
  Animal *lion1 = creer_animal(10,2,3.7);

  Animal *proies = gazelle1;
  Animal *predateurs = lion1;

  //gazelle1 = ajouter_en_tete_animal(gazelle2,gazelle1); -> en cas d'ajout en tete donc gazelle 2 est après gazelle 1
  ajouter_animal(10,2,3.7,&proies);
  ajouter_animal(5,7,1.2,&predateurs);
  ajouter_animal(9,3,9.6,&predateurs);
  proies = ajouter_en_tete_animal(proies, gazelle2);
  proies = ajouter_en_tete_animal(proies, gazelle3);
  printf("Il y a %u proies\n",compte_animal_it(proies));
  printf("Il y a %u predateurs.\n",compte_animal_it(predateurs));

  printf("Texte que je change pour verifier compilation\n");
  afficher_ecosys(proies,predateurs);
  enlever_animal(&predateurs, lion1);
  enlever_animal(&proies, gazelle2);
  afficher_ecosys(proies,predateurs);
  liberer_liste_animaux(proies);
  liberer_liste_animaux(predateurs);
  return 0;
}
