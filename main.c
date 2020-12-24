#include "nim.c"
int main(){
  srand((unsigned int)time(NULL));
//saisie des Parametres
int nlig,ncol,niveau,next;
Parametres(&nlig,&ncol,&niveau,&next);
clrscr();
printf("\n\t\t-------------------\n\t\t   C est Parti !\n\t\t-------------------\n");
//le jeu
T_Case pion={1,1},dernier_pion={nlig,ncol};
T_Tab_Case tab_vois[4];
int coup,nb_vois,nv_pos,grille[VMAX][VMAX];
int Equivalent;
grille_nimber(grille,nlig,ncol);
if (next==2)  coup=1;
else coup=-1;
  do{
      affiche_grille(pion,nlig,ncol);
      Voisines (pion,tab_vois,&nb_vois,nlig,ncol);
      if(coup==1){
        printf("A toi de jouer !\n");
        nv_pos=Coup_joueur(tab_vois,nb_vois);
      }
      else{
        nv_pos=Coup_Ordi(niveau,pion,tab_vois,nb_vois,grille);
        printf("L ordinateur deplace le pion en (%d,%d)\n",tab_vois[nv_pos].Ligne,tab_vois[nv_pos].Colonne);
      }
       pion=tab_vois[nv_pos];
      coup=-1*coup;
      Equivalent=(dernier_pion.Ligne==pion.Ligne)&&(dernier_pion.Colonne==pion.Colonne);
    }while (!Equivalent);
    affiche_grille(pion,nlig,ncol);
    printf("C est termine. ");
    if(coup==-1) printf("BRAVO TU AS GAGNE");
    else printf("vous avez perdu. GAME OVER");
  return 0;
}
