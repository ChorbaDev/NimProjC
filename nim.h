#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef NIM_H
#define NIM_H

//nombre minimum de lignes de la grille
#define VMIN 5
//nombre maximum de lignes de la grille
#define VMAX 30
#define NVMIN 1
#define NVMAX 4
//une fonction qui retourne un nombre au hasard compris entre deux valeurs
#define Hasard(a,b) (rand()%(b-a+1) +a)
#define Coup_Ordi_Hasard(b) (rand()%b)
//structure represente une case de la grille
struct Case{
  int L; //L = nombre de lignes
  int C; //C = nombre de colonnes
} ;
typedef struct Case T_Case; //on renomme struct Case en T_Case

//Un tableau de ce type permettra de stocker l’ensemble des voisines d’une case donnée.
typedef T_Case T_Tab_Case;

//une fonction permet de saisir et de retourner un entier compris entre deux bornes
int Lire_Entier(int BINF,int BSUP) {
  int entier;

  //On demande de saisir un entier compris entre les deux bornes d'intervalles
  printf("Saisir un entier entre %d et %d\n", BINF, BSUP);
  //On lit cet entier
  scanf("%d", entier);
  //Si l'entier est en dehors des bornes, on affiche un message d'erreur
  if (entier < BINF || entier > BSUP)
  {
    printf("Erreur, le nombre %d n'est pas compris dans l'intervalle...\n", entier);
  }
}

//fonction qui calcule le nimber d'une case donnee
int Nimber(T_Case pion,int m[VMAX][VMAX]);

//permet de saisir des donnees
void Parametres(int *nlig,int *ncol,int *niveau,int *next);

//construire le matrice qui contient les nimbers
void grille_nimber(int m[VMAX][VMAX],int nlig,int ncol);

//fonction qui gère le coup d’un joueur
int Coup_joueur (T_Tab_Case t[],int nb_vois);

//fonction qui gère le coup gagnant effectué par l’ordinateur
int Coup_Ordi_Gagnant(T_Case p,T_Tab_Case t[],int n,int m[VMAX][VMAX]);

//une fonction qui construit la table des cases voisines d’une case donnée
void Voisines (T_Case pion,T_Tab_Case t[],int *nb_vois,int nlig,int ncol);

//affichage du grille
void affiche_grille(T_Case pion,int nlig,int ncol);
#endif
