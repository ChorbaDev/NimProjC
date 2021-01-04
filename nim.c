#include "nim.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//fonction qui trouve les voisines
void Voisines(T_Case pion, T_Tab_Case tab_vois[],int *nb_vois,int nlig,int ncol)
{
    //initialisation pt 1
    int i=pion.Colonne;
    int j=0;
    int n=0;
    T_Case vois;
    //calcul du nb de cases voisines
    //calcul des voisines sur la ligne
    while(i+1<=ncol && j<2){
        i++;
        //la ligne reste identique car on travaille sur une seul et même ligne seul la colonne change
        vois.Ligne=pion.Ligne;
        vois.Colonne=i;
        //on stock ça dans tab vois à la position n
        tab_vois[n]=vois;
        n++;
        j++;
    }
    //initialisation pt 2
    i=pion.Ligne;
    j=0;
    //calcul des voisines sur la colonne
    while(i+1<=nlig && j<2){
        i++;
        //la colonne reste identique car on travaille sur une seul et même colonne seul la ligne change
        vois.Ligne=i;
        vois.Colonne=pion.Colonne;
        //on stock ça dans tab vois à la position n
        tab_vois[n]=vois;
        n++;
        j++;
    }
    //nb_vois prend la valeur de n
    *nb_vois=n;
}

//
//
//une fonction qui gère le coup d’un joueur (cette fonction propose au joueur de choisir un coup parmi la liste des coups possibles).

int Coup_joueur (T_Tab_Case tab_vois[],int nb_vois){
    //initialisation
    int i,choix;
    //affichage des choix
    printf("\nChoisir la destination ");
    for (i = 0; i < nb_vois ; i++) {
        printf(" %d : (%d,%d) ",i+1,tab_vois[i].Ligne,tab_vois[i].Colonne);
    }
    //boucle pour lire l'entier
    //on appelle pas la fct Lire_Entier pour des raisons d'affichage
    do {
        printf("\n---> ");
        scanf("%d",&choix);
        getchar();
        if (choix>nb_vois){
            printf("Erreur !");
        }
    } while (choix>nb_vois);
    //on décremente le choix de 1 pour pouvoir l'utiliser dans le tableau selon les regles
    return (choix-1);
}

//
//
//une fonction qui gère le coup gagnant effectué par l’ordinateur(jouer une position gagnante si possible, sinon jouer un coup au hasard)

int Coup_Ordi_Gagnant(T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol){
    //initialisation
    int pos,nv_pos,ver_pos;//nimber de la position actuelle, nouvelle position, nimber postition hypothétique
    int i;
    T_Case ver_case;//position d'un pion hypothetique
    pos = Nimber(pion,nlig,ncol);
    //d'après l'ennoce sur la stratégie gagnante, on a besoin de rentrer dans la condition
    //uniquement lorsque le nimber de la position du pion actuelle est de 1

    if (pos==1) {
        for (i = 0;  i<nb_vois ; i++)
        {
            //la case voisine à la position i dans le tableau doit être verifiée
            ver_case = tab_vois[i];
            //on verfie donc le nimber de cette position
            ver_pos = Nimber(ver_case, nlig, ncol);
            //si la condition est verifiée on a pas besoin de continuer la boucle on sort directement
            if (ver_pos==0)
            {
                break;
            }
        }
        //on demande à l'ordinateur de choisir la nouvelle position qui est bien sûr i lorsque celui-ci à pour ver_pos 0
        nv_pos = i;
    }
    //sinon on opère au hasard
    else
        nv_pos=Coup_Ordi_Hasard(nb_vois);
    return nv_pos;

}

//
//
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
    system("@cls||clear");//problème lors de l'execution sur Ubuntu sh: 1: @cls: not found
}

//Lecture d'un entier compris entre BINF et BSUP
int Lire_Entier(int BINF,int BSUP)
{
  /* Définition des variables */
  int entier;
  int correct;
  /* Fonction */
  do {
    scanf("%d",&entier); //on lit l'entier
    getchar();
    correct = (entier >= BINF && entier <= BSUP); //l'entier est correct si il est compris entre VMIN et VMAX
    if (correct == 0) //Si l'entier n'est pas correct (en dehors de l'intervalle)
    {
      printf("Erreur !\n"); //On affiche un message d'erreur
    }
  } while (!correct);
  return entier; //On retourne l'entier
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
        if(j>9) printf(" ");
        printf("0|");
      }
      else{
        if(j>9) printf("-");
          printf("-|");
      }

    }
    printf("\n");
  }
}
