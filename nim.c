#include "nim.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//fonction qui permet de remplir la grille par des nimbers
/*void grille_nimber(int m[VMAX][VMAX],int nlig,int ncol){
int i,j,x=0;
  for(i=ncol-1;i>=0;i--){
    for(j=nlig-1;j>=0;j--){
      m[j][i]=(x==0)?0:1;
      x=(x==2)?0:x+1;
    }
  }
}
//fonction qui calcule le nimber d'une case donnee
int Nimber(T_Case pion,int m[VMAX][VMAX]){
  int i=pion.Ligne-1,j=pion.Colonne-1;
  return m[i][j];
}*/
//fonction qui trouve les voisines
void Voisines(T_Case pion, T_Tab_Case tab_vois[],int *nb_vois,int nlig,int ncol)
{
    int i=pion.Colonne;
    int j=0;
    int n=0;
    int k;
    //calcul du nb de cases voisines
    //calcul des voisines horizontalement
    while(i<ncol && j<2){
        T_Case vois;
        i++;
        vois.Ligne=pion.Ligne;
        vois.Colonne=i;
        tab_vois[n]=vois;
        n++;
        j++;
    }
    i=pion.Ligne;
    j=0;
    //calcul des voisines verticalement
    while(i<nlig && j<2){
        T_Case vois;
        i++;
        vois.Ligne=i;
        vois.Colonne=pion.Colonne;
        tab_vois[n]=vois;
        n++;
        j++;
    }
    //la valeur de nb_vois prend la valeur de n
    *nb_vois=n;
}
//
//
//une fonction qui gère le coup d’un joueur (cette fonction propose au joueur de choisir un coup parmi la liste des coups possibles).
int Coup_joueur (T_Tab_Case tab_vois[],int nb_vois){
    int i,choix, nv_pos;
    printf("\nChoisir la destination ");
    for (i = 0; i < nb_vois ; i++) {
        printf(" %d : (%d,%d) \t",i+1,tab_vois[i].Ligne,tab_vois[i].Colonne);
    }
    do {
        scanf("%d",&choix);
        getchar();
        if (choix>nb_vois){
            printf("Erreur !");
        }
    } while (choix>nb_vois);
    nv_pos=choix-1;
    return nv_pos;
}
//
//
//une fonction qui gère le coup gagnant effectué par l’ordinateur(jouer une position gagnante si possible, sinon jouer un coup au hasard)
/*int Coup_Ordi_Gagnant(T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){

}*/
//
int Coup_Ordi(int niveau,T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
  int proba,nv_pos;
  switch(niveau){
    case 1:nv_pos=Coup_Ordi_Hasard(nb_vois);break;
    case 4:nv_pos=Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol);break;
    default:
    proba=Hasard(1,3);
      if (niveau==2)
          nv_pos=(proba<=2)?Coup_Ordi_Hasard(nb_vois):Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol);
      else
         nv_pos=(proba==3)?Coup_Ordi_Hasard(nb_vois):Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol);
  }
  return nv_pos;
}
//pour trouver le Nimber d'un coolonne donnee
int Nimber(T_Case pion,int nlig,int ncol){
  int nim;
  int x=pion.Colonne,y=pion.Ligne;
    while(y!=nlig && x!=ncol){
      x++;
      y++;
    }
    nim=(x==ncol)?(((nlig-y)%3==0)?0:1):(((ncol-x)%3==0)?0:1);
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
//"TO CLEAR THE SCREEN"
void clrscr()
{
    system("@cls||clear");
}

//Lecture d'un entier compris entre BINF et BSUP
int Lire_Entier(int BINF,int BSUP)
{
  int entier = 0;
  if ()
  {
  do {
  printf("Saisir un entier compris entre %d et %d\n", BINF, BSUP); //on demande la saisie de l'entier et on affiche l'intervalle
  scanf("%d",&entier); //on lit l'entier
  } while (entier < BINF || entier > BSUP);
  }
  else
  {
    printf("Erreur");
  }
  
  return 0;
}

//Affichage des paramètres du jeu (nombre colonnes/lignes/niveau...)
void Parametres(int *nlig, int *ncol, int *niveau, int *next) {
  printf("Parametres du jeu :"); 
  do
  {
    printf("\nNombre de lignes :"); //on demande le nombre de lignes
    scanf(nlig);
  } while (nlig < VMIN || nlig > VMAX); //on vérifie que le nombre de lignes est compris dans l'intervalle donnée
  
  do
  {
    printf("\nNombre de colonnes:"); //on demande le nombre de colonnes
    scanf(ncol);
  } while (ncol < VMIN || ncol > VMAX); //on vérifie que le nombre de colonnes est compris dans l'intervalle donnée
  
  do
  {
    printf("\nNiveau de 1 a 4 :"); //on demande de choisir le niveau
    scanf(niveau);
  } while (niveau < 1 || niveau > 4); //on vérifie que le niveau est compris entre 1 et 4
  
  printf("\n Qui commence ?\n"); //on demande qui commence
  do
  {
    printf("L'ordinateur (1) ou le joueur (2) ?\n"); //choix de qui commence
    scanf(next);
  } while (next < 1 || next > 2); //on redemande si next est différent de 1 ou 2
  printf("C'est parti !"); //afficher début partie
}