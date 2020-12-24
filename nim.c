#include "nim.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//fonction qui permet de remplir la grille par des nimbers
void grille_nimber(int m[VMAX][VMAX],int nlig,int ncol){
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
}
//fonction qui trouve les voisines
void Voisines(T_Case pion, T_Tab_Case tab_vois[],int *nb_vois,int nlig,int ncol)
{
    int i=pion.Colonne;
    int j=0;
    //calcul du nb de cases voisines
    //calcul des voisines horizontalement
    while(i<ncol && j<2){
        T_Case vois;
        i++;
        vois.Ligne=pion.Ligne;
        vois.Colonne=i;
        tab_vois[*nb_vois]=vois;
        nb_vois++;
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
        tab_vois[*nb_vois]=vois;
        nb_vois++;
        j++;
    }
}
//"TO CLEAR THE SCREEN"
void clrscr()
{
    system("@cls||clear");
}
