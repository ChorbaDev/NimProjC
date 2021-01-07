#include "nim.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//fonction qui trouve les voisines
void Voisines(T_Case pion, T_Tab_Case tab_vois[],int *nb_vois,int nlig,int ncol)
{
    int i=pion.Colonne;
    int j=0;
    int n=0;
    T_Case vois;
    //calcul des voisines sur la ligne
    while(i+1<=ncol && j<2){
        i++;
        vois.Ligne=pion.Ligne;
        vois.Colonne=i;
        tab_vois[n]=vois;
        n++;
        j++;
    }
    i=pion.Ligne;
    j=0;
    //calcul des voisines sur la colonne
    while(i+1<=nlig && j<2){
        i++;
        vois.Ligne=i;
        vois.Colonne=pion.Colonne;
        tab_vois[n]=vois;
        n++;
        j++;
    }
    *nb_vois=n;
}


//une fonction qui gère le coup d’un joueur (cette fonction propose au joueur de choisir un coup parmi la liste des coups possibles).
int Coup_joueur (T_Tab_Case tab_vois[],int nb_vois){
    int i,choix;
    //affichage des choix
    printf("\nChoisir la destination ");
    for (i = 0; i < nb_vois ; i++) {
        printf(" %d : (%d,%d) ",i+1,tab_vois[i].Ligne,tab_vois[i].Colonne);
    }
    //on appelle pas la fct Lire_Entier pour des raisons d'affichage
    do {
        printf("\n---> ");
        scanf("%d",&choix);
        getchar();
        if (choix>nb_vois){
            printf("Erreur !");
        }
    } while (choix>nb_vois);
    //on décremente le choix de 1 pour pouvoir l'utiliser dans le tableau selon les regles de syntaxe
    return (choix-1);
}


//une fonction qui gère le coup gagnant effectué par l’ordinateur(jouer une position gagnante si possible, sinon jouer un coup au hasard)
int Coup_Ordi_Gagnant(T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
    int nim_pos,nv_pos,nim_nv_pos;
    int i;
    T_Case nv_pion;
    nim_pos = Nimber(pion,nlig,ncol);
    //d'après l'ennoce sur la stratégie gagnante
    if (nim_pos==1) {
        //verif du nimber de la nouvelle position
        for (i = 0;  i<nb_vois ; i++)
        {
            nv_pion = tab_vois[i];
            nim_nv_pos = Nimber(nv_pion, nlig, ncol);

            if (nim_nv_pos==0)
            {
                break;
            }
        }
        //choix de l'ordinateur
        nv_pos = i;
    }
    else
        nv_pos=Coup_Ordi_Hasard(nb_vois);
    return nv_pos;
}


//la fonction qui determine le coup de l'ordinateur qui depend de niveau
int Coup_Ordi(int niveau,T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
  int proba,nv_pos;
  switch(niveau){
    case 1:nv_pos=Coup_Ordi_Hasard(nb_vois);break;
    case 4:nv_pos=Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol); break;
    default:
    proba=Hasard(1,3);//un nombre au hasard entre 1 et 3
      if (niveau==2)
          nv_pos=(proba==3)?Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol):Coup_Ordi_Hasard(nb_vois); //si le niveau=2 et si proba=3 et <> 2 et 1 c.a.d 1/3 de la probabilite coup gagnant sinon coup hasard
      else
         nv_pos=(proba==3)?Coup_Ordi_Hasard(nb_vois):Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol);//si le niveau=3 et si proba=3 et <> 2 et 1 c.a.d 1/3 de la probabilite coup au hasard sinon coup gagnant
  }
  return nv_pos; //c'est une fonction avec retoure ce qui est la position de coup de l'ordinateur dans le tableau des voisines
}


//pour trouver le Nimber d'une case donnee
int Nimber(T_Case pion,int nlig,int ncol){
  int nim;
  int x=pion.Colonne,y=pion.Ligne;
  //on va decaler le pion vers l'avant jusqu'a on se retrouve dans la derniere ligne ou derniere colonne
    while(y!=nlig && x!=ncol){
      x++;
      y++;
    }
    nim=(x==ncol)?(((nlig-y)%3==0)?0:1):(((ncol-x)%3==0)?0:1);

//c'est juste l'ecriture plus detaille de la ligne juste au dessus
   /*if(x==ncol)
      if((nlig-y)%3==0)
        nim=0;
        else
        nim=1;
    else
        if((ncol-x)%3==0)
          nim=0;
        else
          nim=1;
     */
     return nim;
}


//Lecture d'un entier compris entre BINF et BSUP
int Lire_Entier(int BINF,int BSUP)
{
  int entier;
  int correct;
  do {
    scanf("%d",&entier);
    getchar();
    correct = (entier >= BINF && entier <= BSUP); //l'entier est correct si il est compris entre VMIN et VMAX
    if (correct == 0) //Si l'entier n'est pas correct (en dehors de l'intervalle)
    {
      printf("Erreur !\n");
    }
  } while (!correct);
  return entier;
}


/* Affichage des paramètres du jeu (nombre colonnes/lignes/niveau...) */
void Parametres(int *nlig, int *ncol, int *niveau, int *next) {
  printf("Parametres du jeu :");

  /* Nombre de lignes */
  printf("\nNombre de lignes :");
  *nlig = Lire_Entier(VMIN, VMAX);

  /* Nombre de colonnes */
  printf("Nombre de colonnes:");
  *ncol = Lire_Entier(VMIN, VMAX);

  /* Choix niveau */
  printf("Niveau de %d a %d : ",NVMIN,NVMAX);
  *niveau = Lire_Entier(NVMIN, NVMAX);

  /* Choix joueur qui commence */
  printf("Qui commence ?\n");
  printf("L'ordinateur (1) ou le joueur (2) ? ");
  *next = Lire_Entier(1,2);
}


/* Affichage de la grille  */
void affiche_grille(T_Case pion,int nlig,int ncol) {
  int j,i;
  /* Affichage nombre de colonnes */
    printf("  ");
  for (j = 1; j <= ncol; j++)
  {
  //  if(j<10) printf("%s\n", );
    printf(" %d", j); //Ici on affiche les numéros de chaque colonne
  }
  printf("\n");
  /* Affichage nombre de lignes */
  for (i = 1; i <= nlig; i++)
  {
    if(i<10) printf(" ");
    printf("%d|", i); //On affiche le numéro de la ligne
    for (j = 1; j <= ncol; j++)
    {
      if((pion.Ligne==i)&&(pion.Colonne==j)){
        if(j>9) printf(" "); //affichage d'un espace pour garder l'affichage de la grille
        printf("0|");
      }
      else{
        if(j>9) printf("-"); //on affiche un autre - pour ne pas que l'affichage soit décalé
          printf("-|");
      }

    }
    printf("\n");
  }
}
