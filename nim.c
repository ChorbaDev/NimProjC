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
    T_Case vois;
    //calcul du nb de cases voisines
    //calcul des voisines horizontalement
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
    //calcul des voisines verticalement
    while(i+1<=nlig && j<2){
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
    int i,choix;
    printf("\nChoisir la destination ");
    for (i = 0; i < nb_vois ; i++) {
        printf(" %d : (%d,%d) ",i+1,tab_vois[i].Ligne,tab_vois[i].Colonne);
    }
    do {
        printf("\n---> ");
        scanf("%d",&choix);
        if (choix>nb_vois){
            printf("Erreur !");
        }
    } while (choix>nb_vois);
    return (choix-1);
}
//
//
//une fonction qui gère le coup gagnant effectué par l’ordinateur(jouer une position gagnante si possible, sinon jouer un coup au hasard)
int Coup_Ordi_Gagnant(T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
    int pos,nv_pos,ver_pos;//nimber de la position actuelle, nouvelle position, nimber postition hypothétique
    int i=0;
    T_Case ver_case;//position d'un pion hypothetique
    pos = Nimber(pion,nlig,ncol);
//    printf("pos=%d\n",pos);
    if (pos==1) {
        do {
            ver_case = tab_vois[i];
//            printf("ver_case=%d \n",ver_case);
            ver_pos = Nimber(ver_case, nlig, ncol);
            if (ver_pos==0){
                break;
            }
            else
//            printf("ver_pos=%d \n",ver_pos);
                i++;
//            printf("i=%d\n",i);
        } while (ver_pos != 0);
        nv_pos = i;
//        printf("nv_pos=%d \n", nv_pos);

    }
    else
        nv_pos=Coup_Ordi_Hasard(nb_vois);
    return nv_pos;

}
//
int Coup_Ordi(int niveau,T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
  int proba,nv_pos;
  switch(niveau){
    case 1:nv_pos=Coup_Ordi_Hasard(nb_vois);break;
    case 4:nv_pos=Coup_Ordi_Gagnant(pion,tab_vois,nb_vois,nlig,ncol); break;
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
//      printf("y=%d,x=%d \n",y,x);
    }
    nim=(x==ncol)?(((nlig-y)%3==0)?0:1):(((ncol-x)%3==0)?0:1);
//    printf("nim=%d\n",nim);
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
    system("@cls||clear");//problème lors de l'execution sur Ubuntu sh: 1: @cls: not found
}

//Lecture d'un entier compris entre BINF et BSUP
int Lire_Entier(int BINF,int BSUP)
{
  /* Définition des variables */
  int entier;
  int correct;
  /* Programme */
  do {
    scanf("%d",&entier); //on lit l'entier
    getchar();
    correct = (entier >= BINF && entier <= BSUP);
    if (correct == 0)
    {
      printf("Erreur\n");
    }
  } while (!correct);
  return entier;
}

/* Affichage des paramètres du jeu (nombre colonnes/lignes/niveau...) */
void Parametres(int *nlig, int *ncol, int *niveau, int *next) {
  printf("Parametres du jeu :");

  /* Nombre de lignes */
  printf("\nNombre de lignes :"); //on demande le nombre de lignes
  *nlig = Lire_Entier(VMIN, VMAX);

  /* Nombre de colonnes */
  printf("Nombre de colonnes:"); //on demande le nombre de colonnes
  *ncol = Lire_Entier(VMIN, VMAX);

  /* Choix niveau */
  printf("Niveau de %d a %d : ",NVMIN,NVMAX); //on demande de choisir le niveau
  *niveau = Lire_Entier(NVMIN, NVMAX); //on vérifie que le niveau est compris entre 1 et 4

  /* Choix joueur qui commence */
  printf("Qui commence ?\n"); //on demande qui commence
  printf("L'ordinateur (1) ou le joueur (2) ? "); //choix de qui commence
  *next = Lire_Entier(1,2); //on redemande si next est différent de 1 ou 2
}

/* Affichage de la grille  */
void affiche_grille(T_Case pion,int nlig,int ncol) {
  /* Définition des variables */
  int j,i;
  /* Affichage nombre de colonnes */
    printf(" ");
  for (j = 1; j <= ncol; j++)
  {
    printf(" %d", j); //Ici on affiche les numéros de chaque colonne
  }
  printf("\n");
  /* Affichage nombre de lignes */
  for (i = 1; i <= nlig; i++)
  {
    printf("%d|", i); //On affiche le numéro de la ligne
    for (j = 1; j <= ncol; j++)
    {
      if((pion.Ligne==i)&&(pion.Colonne==j))
        printf("0|");
      else
        printf("-|");
    }
    printf("\n"); //retour à la ligne
  }
  SDL_Delay(1000); //on attends une seconde
}
//prochaine étape ajouter un delai
