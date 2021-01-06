#ifndef NIM_H
#define NIM_H
//nombre minimum de lignes de la grille
#define VMIN 5
//nombre maximum de lignes de la grille
#define VMAX 30
//niveau minimum
#define NVMIN 1
//nievau maximum
#define NVMAX 4
//une fonction qui retourne un nombre au hasard compris entre deux valeurs
#define Hasard(a,b) (rand()%(b-a+1) +a)
//le coup au hasard de l'ordinateur
#define Coup_Ordi_Hasard(b) (rand()%b)
//structure represente une case de la grille
struct Case{
  int Ligne;
  int Colonne;
};
//renommer la structure case par t_case
typedef struct Case T_Case;
//Un tableau de ce type permettra de stocker l’ensemble des voisines d’une case donnée.
typedef T_Case T_Tab_Case;
//une fonction permet de saisir et de retourner un entier compris entre deux bornes.
int Lire_Entier(int BINF,int BSUP);
//permet de saisir des donnees
void Parametres(int *nlig,int *ncol,int *niveau,int *next);
//fonction qui gère le coup d’un joueur
int Coup_joueur (T_Tab_Case tab_vois[],int nb_vois);
//fonction qui gère le coup gagnant effectué par l’ordinateur
int Coup_Ordi_Gagnant(T_Case pion,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol);
//une fonction qui construit la table des cases voisines d’une case donnée
void Voisines (T_Case pion,T_Tab_Case tab_vois[],int *nb_vois,int nlig,int ncol);
//affichage du grille
void affiche_grille(T_Case pion,int nlig,int ncol);
//retourne la position dans le tableau des voisines dont l'ordinateur a choisie
int Coup_Ordi(int niveau,T_Case pi,T_Tab_Case tab_vois[],int nb_vois,int nlig,int ncol);
//pour trouver le Nimber d'un colonne donnee
int Nimber(T_Case pion,int nlig,int ncol);
#endif
