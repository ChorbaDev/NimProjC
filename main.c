#include "nim.c"
int main(){
  srand((unsigned int)time(NULL));
//saisie des Parametres
/* Définition des variables */
int nlig,ncol,niveau,next;
int coup,nb_vois,nv_pos;
int Equivalent;
/* Programme princiapal */
Parametres(&nlig,&ncol,&niveau,&next);
printf("\n\t\t-------------------\n\t\t   C est Parti !\n\t\t-------------------\n");
//le jeu
T_Case pion={1,1},dernier_pion={nlig,ncol};
T_Tab_Case tab_vois[4];
if (next==2)
  coup=1;
else
  coup=-1;
  do{
        printf("\n");
      affiche_grille(pion,nlig,ncol); //l'affichage de la grille avec la position actuelle du pion
        printf("\n");
      Voisines (pion,tab_vois,&nb_vois,nlig,ncol); //remplir le tableau des voisines a chaque fois la position de pion ce change
      if(coup==1){
        printf("A toi de jouer !\n");
        nv_pos=Coup_joueur(tab_vois,nb_vois); //le choix de joueur de nouvelle position de pion parmi les voisines
      }
      else{
        nv_pos=Coup_Ordi(niveau,pion,tab_vois,nb_vois,nlig,ncol); // le coup de l'ordinateur depend de niveau
        printf("L'ordinateur deplace le pion en (%d,%d)\n",tab_vois[nv_pos].Ligne,tab_vois[nv_pos].Colonne);
      }
       pion=tab_vois[nv_pos]; // affecter a pion la nouvelle position
        coup=-1*coup; // pour determiner le coup, 1 pour le joueur et -1 pour l'ordinateur
      Equivalent=(dernier_pion.Ligne==pion.Ligne)&&(dernier_pion.Colonne==pion.Colonne); // verifier si la position de pion et egale a la dernier case dans la grille
    }while (!Equivalent);
    //fin de jeu
    affiche_grille(pion,nlig,ncol);
    printf("\nC est termine. ");
    if(coup==-1) printf("BRAVO TU AS GAGNE"); //affichage du résultat (gagnant ou perdant)
    else printf("Vous avez perdu. GAME OVER");
  return 0;
}
