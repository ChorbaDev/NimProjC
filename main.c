#include <stdio.h>

int main(){
//Création d'un Menu de choix de difficulté du jeu
int ChoixDifficulte;

printf("Choix de la difficulte :\n");
printf("1. Niveau debutant\n");
printf("2. Niveau moyen\n");
printf("3. Niveau expert\n");
printf("4. Niveau virtuose\n");
printf("Veuillez entrer un nombre entre 1 et 4 :\n");
scanf("%d\n", &ChoixDifficulte);

  switch (ChoixDifficulte)
  {
  case 1:
    printf("Vous avez choisi le niveau debutant !\n");
    break;
  
    case 2:
    printf("Vous avez choisi le niveau moyen !\n");
    break;

    case 3:
    printf("Vous avez choisi le niveau expert !\n");
    break;

    case 4:
    printf("Vous avez choisi le niveau virtuose !\n");
    break;

  default:
  printf("Vous n'avez pas entre de nombre correct...\n");
    break;
  }

  return 0;
}