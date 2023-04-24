#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

int tab_herbe[SIZE_X][SIZE_Y];
int nbIt=0;

int main(void) {
  for(int i=0; i < SIZE_X;i++){
    for(int j=0; j < SIZE_Y ; j++){
      tab_herbe[i][j]=0;
    }
  }
  srand(time(NULL)); // Initialisation de rand() afin d'obtenir une position "pseudo aléatoire" à chaque execution de l'ecosystème

  //création de 20 proies avec une position x et y aléatoire et une énergie arbitrairement fixé à 20

  Animal *gazelle = creer_animal(rand() % (SIZE_X-2)+1, rand() % (SIZE_Y-2)+1,20);

  for(int i = 1 ; i < NB_PROIES ; i++){ //création de 19 autres proies

    ajouter_animal(rand() % (SIZE_X-2)+1, rand() % (SIZE_Y-2)+1, 10, &gazelle);

  }

  //création de 20 prédateurs avec une position x et y aléatoire et une énergie arbitrairement fixé à 20

  Animal *lion =creer_animal(rand() % (SIZE_X-2)+1, rand() % (SIZE_Y-2)+1,20);

  for(int i = 1 ; i < NB_PREDATEURS ; i++){ //création de 19 autres prédateurs

    ajouter_animal(rand() % (SIZE_X-2)+1, rand() % (SIZE_Y-2)+1, 20, &lion);
  }

  // mise à jour de l'ecosysteme :

  FILE *file = fopen("Evol_Pop.txt", "w"); //Ouverture du fichier en écriture
  
  if(file==NULL){ // gestion en cas d'une erreur empéchant l'ouverture du fichier

    printf("Erreur à l'ouverture du fichier\n");

    return 0;
  }

  afficher_ecosys(gazelle, lion); //Affichage de l'état initial de notre écosystème
  printf("Voici l'état initial de notre monde.\n");

  int nbMaxIt;
	printf("Nombre max d'iteration ?\t"); 
	scanf("%d",&nbMaxIt); //demande à l'utilisateur le nombre max d'iteration que le programme doit effectuer

  while(compte_animal_it(gazelle)>0 && nbIt<nbMaxIt){

    fprintf(file,"%d %d %d\n", nbIt, compte_animal_it(gazelle), compte_animal_it(lion)); //écriture dans le fichier Evol_Pop.txt pour chaque itération du numéro de l'itération actuelle, du nombre de proies et de prédateurs restants
    //actualisation des proies, predateurs, du monde (herbe) et affichage de l'ecosystème
    rafraichir_proies(&gazelle, tab_herbe);
    rafraichir_predateurs(&lion, &gazelle);
    rafraichir_monde(tab_herbe);
    afficher_ecosys(gazelle, lion);
    //incrémentation du nombre d'itération et son affichage
    nbIt++;
    printf("Itération n° %d\n", nbIt);
    
    //ajout d'une "pause" d'un temps T_WAIT en millisecondes afin de pouvoir observer l'évolution de notre écosystème
    usleep(T_WAIT);
  }
  fprintf(file,"%d %d %d\n", nbIt, compte_animal_it(gazelle), compte_animal_it(lion)); //écriture pour le dernier tour dans le fichier Evol_pop.txt
  
  fclose(file); //Fermeture du fichier et libération de la mémoire allouée pour la gestion de l'écriture

  //libération de la mémoire alloués pour nos proies et prédateurs
  liberer_liste_animaux(gazelle);
  liberer_liste_animaux(lion);

  printf("main_ecosys.c\n");
  return 0;
}
