#include "header.h"

void couleur(const char* param) {
    printf("\033[%sm", param);
}

void mettreAJourScores(Joueur joueurs[], int joueurCourant, int nbrcoup, int deplacementsrobots, int r, int nb_joueurs){
  if (nbrcoup < deplacementsrobots) {

      // Le joueur qui joue ne marque aucun point, et les autres marquent 1 point chacun
      printf("Le robot a atteint sa cible bien trop lentement le tout le monde marque donc un point sauf le joueur qui viens de jouer\n");
      for (int i = 0; i <  nb_joueurs; i++) {
          if (i != r) {
              joueurs[i].score += 1;
          }
      }
  }
              // Le joueur qui joue marque 2 points
              else if (nbrcoup == deplacementsrobots) {
                  printf("Le robot a atteint sa cible comme il était prévu, le joueur venant de jouer marque donc 2 points\n");
                  joueurs[r].score += 2;
              }
                  // Le joueur qui joue perd 1 point
                  else if(nbrcoup > deplacementsrobots){
                      printf("le robot a ateint sa cible plus rapidement que prévu, donc le joueur qui viens de jouer perd 1 point\n");
                  joueurs[joueurCourant].score -= 1;
              }
}


int obtenirGagnant(Joueur joueurs[], int nb_joueurs) {
  int scoreMax = joueurs[0].score;
  int indiceGagnant = 0;
  for (int i = 1; i < nb_joueurs; i++) {
      if (joueurs[i].score > scoreMax) {
          scoreMax = joueurs[i].score;
          indiceGagnant = i;
      }
  }
  return indiceGagnant;
}

//Fonction pour afficher le score de chacun et qui est le joueur avec le plus de point
void afficherScores(Joueur joueurs[], int nb_joueur, char n) {
  printf("Scores :\n");
  for (int i = 0; i < nb_joueur; i++) {
      printf("Joueur %s : %d points\n", joueurs[i].nom, joueurs[i].score);
  }
  int indiceGagnant = obtenirGagnant(joueurs, nb_joueur);
  printf("Gagnant : %s avec %d points\n", joueurs[indiceGagnant].nom, joueurs[indiceGagnant].score);

}


// Grille de jeu avec +1 ajouté aux dimensions
char grille[MAX_RANGEES + 1][MAX_COLONNES + 1]; 

void initialiserGrille(int rangees, int colonnes) {
  // Initialisation de la grille avec des murs sur les bords
  for (int i = 0; i <= rangees; i++) { 
      for (int j = 0; j <= colonnes; j++) {
          if (i == 0 || i == rangees || j == 0 || j == colonnes) {
              grille[i][j] = '#'; // Caractère pour les murs
          } else {
              grille[i][j] = '-'; // Caractère pour l'intérieur de la grille
          }
      }
  }

  int row1, row2, col1, col2;

  // Murs horizontaux
  do {
      row1 = rand() % (rangees - 3) + 2; // Exclut les bords de la grille et une marge pour les murs
      row2 = rand() % (rangees - 3) + 2; // Exclut les bords de la grille et une marge pour les murs
  } while (abs(row1 - row2) <= 2);

  grille[row1][1] = '*';
  grille[row1][colonnes - 1] = '*';
  grille[row2][1] = '*';
  grille[row2][colonnes - 1] = '*';

  // Murs verticaux
  do {
      col1 = rand() % (colonnes - 3) + 2; // Exclut les bords de la grille et une marge pour les murs
      col2 = rand() % (colonnes - 3) + 2; // Exclut les bords de la grille et une marge pour les murs
  } while (abs(col1 - col2) <= 2);

  grille[1][col1] = '*';
  grille[rangees - 1][col1] = '*';
  grille[1][col2] = '*';
  grille[rangees - 1][col2] = '*';
}

// Place les cibles sur la grille de manière aléatoire, en les entourant d'un mur formant un angle droit
void placerCibles(Cible cibles[]) {
  for (int i = 0; i < NB_CIBLES; i++) {
      int x, y;
      int positionValide;
      do {
          x = rand() % (MAX_RANGEES - 4) + 2;  // Exclut les bords de la grille et une marge pour les murs
          y = rand() % (MAX_COLONNES - 4) + 2;  // Exclut les bords de la grille et une marge pour les murs
          positionValide = 1;

          // Vérifie que toutes les cases dans un rayon de deux cases autour de la position choisie sont libres
          for (int dx = -2; dx <= 2; dx++) {
              for (int dy = -2; dy <= 2; dy++) {
                  if (grille[x + dx][y + dy] != '-') {
                      positionValide = 0;
                      break;
                  }
              }
              if (!positionValide) {
                  break;
              }
          }
      } while (!positionValide);

      int angleAleatoire = rand() % 4; 

      if (angleAleatoire == 0) {
          // Place l'angle inférieur droit
          grille[x + 1][y + 1] = '@'; // Angle inférieur droit
          grille[x][y + 1] = '|';     // Mur à droite
          grille[x + 1][y] = '+';     // Mur en bas
      } else if (angleAleatoire == 1) {
          // Place l'angle inférieur gauche
          grille[x - 1][y + 1] = '@'; // Angle inférieur gauche
          grille[x][y + 1] = '|';     // Mur à droite
          grille[x - 1][y] = '+';     // Mur en bas
      } else if (angleAleatoire == 2) {
          // Place l'angle supérieur droit
          grille[x + 1][y - 1] = '@'; // Angle supérieur droit
          grille[x][y - 1] = '|';     // Mur à gauche
          grille[x + 1][y] = '+';     // Mur en haut
      } else if (angleAleatoire == 3) {
          // Place l'angle supérieur gauche
          grille[x - 1][y - 1] = '@'; // Angle supérieur gauche
          grille[x][y - 1] = '|';     // Mur à gauche
          grille[x - 1][y] = '+';     // Mur en haut
      }

      grille[x][y] = 'A' + i; // Utilisation de lettres pour les cibles
      cibles[i].symbole = 'A' + i; // Stocker le symbole de la cible
      cibles[i].numero = i + 1;
      cibles[i].position.x = x;
      cibles[i].position.y = y;
  }
}

// Place les robots sur la grille de manière aléatoire
void placerRobots(Robot robots[]) {
  char symboles[] = {'r', 'x', 'y', 'z'}; // caractères pour les robots

  for (int i = 0; i < NB_ROBOTS; i++) {
      int x, y;

      // Cherche une position vide
      do {
          x = rand() % (MAX_RANGEES + 1); // Inclut la nouvelle dimension
          y = rand() % (MAX_COLONNES + 1); // Inclut la nouvelle dimension
      } while (grille[x][y] != '-' || grille[x - 1][y] != '-' || grille[x + 1][y] != '-' || grille[x][y - 1] != '-' || grille[x][y + 1] != '-'); // endroit ou on ne place pas les robots

      // Place le robot sur la grille
      grille[x][y] = symboles[i]; // Symbole pour le robot
      robots[i].symbole = symboles[i];
      robots[i].position.x = x;
      robots[i].position.y = y;
  }
}

// affichage de la grile
void afficherMurs(int rangees, int colonnes) {
  for (int i = 0; i <= rangees; i++) { // <= pour inclure la nouvelle dimension
      for (int j = 0; j <= colonnes; j++) { // <= pour inclure la nouvelle dimension
          if (grille[i][j] == '#' || grille[i][j] == '*' || grille[i][j] == '@' || grille[i][j] == '+' || grille[i][j] == '|') {
              couleur("31");
              printf("■ ");
              couleur("0");
          } else if (grille[i][j] >= 'A' && grille[i][j] <= 'R') {
              couleur("34");
              printf("%c ", grille[i][j]);
              couleur("0");
          } else if (grille[i][j] == 'r') {
              printf("🐧");
          } else if (grille[i][j] == 'x') {
              printf("🐶");
          } else if (grille[i][j] == 'y') {
              printf("🐱");
          } else if (grille[i][j] == 'z') {
              printf("🐴");
          } else if (grille[i][j] == '-') {
              couleur("32");
              printf("- ");
              couleur("0");
          } else {
              printf("%c ", grille[i][j]);
          }
      }
      printf("\n");
  }
}


Resultat  affichageElements(Robot robots[], Joueur joueurs[], int joueurCourant, int manche, int rangees, int colonnes) {
   int res = 0;
   int premiere_manche = 0;
   static int nb_joueur = 0;

// entrer le nombre de joueur
       if(manche == 0) {
           do{
           printf("Nombre de joueurs : ");
           res = scanf("%d", &nb_joueur);
           if (nb_joueur < 2 || res != 1) {
               printf("Erreur veuillez saisir un chiffre ou nombre superieur à 2.\n");
           }
               while (getchar() != '\n');

       } 
               while (nb_joueur < 2 || res != 1);

       for (int i = 0; i < nb_joueur; i++) {
           printf("Entrez le nom du Joueur %d : ", i + 1);
           scanf("%s", joueurs[i].nom);
           for (int j = 0; j < i; j++) {
               if (strcmp(joueurs[j].nom, joueurs[i].nom) == 0) {
                   printf("Erreur: Ce nom est déjà utilisé par un autre joueur. Veuillez choisir un autre nom.\n");
                   i--;
                   j = i;
                   break;
               }
           }
           joueurs[i].score = 0;
       }

      premiere_manche ++;
           //printf("NOMBRE DE LA PREMIERE MANCHE :%d", premiere_manche);

   }//while(premiere_manche == 0);


   for (int i = 0; i < nb_joueur; i++) {
       printf("Voici le robot pour le Joueur %s : \n", joueurs[i].nom);
       if (nb_joueur >= 1) {
           switch (i % nb_joueur) {
               case 0: printf("🐧\n"); break;
               case 1: printf("🐶\n"); break;
               case 2: printf("🐱\n"); break;
               case 3: printf("🐴\n"); break;
               default: printf("Erreur dans la sélection du robot\n"); exit(EXIT_FAILURE);
           }
       }
   }

   int niveau;



   do {
           printf("Quel niveau de difficulté souhaitez-vous ?\n");
           printf("Entrez :\n1 pour facile\n2 pour moyen\n3 pour difficile\n\nVotre choix : ");

           if ((res = scanf("%d", &niveau)) != 1) {
               printf("L'entrée n'est pas valide.\n");
               printf("Veuillez réessayer.\n");
               // Vider le buffer pour éviter une boucle infinie en cas d'entrée non valide
               while (getchar() != '\n');
           } else {
               switch (niveau) {
                   case 1:
                       printf("Très bien, allons-y pour le niveau facile\n");
                       creationMinuteur(40);
                       break;
                   case 2:
                       printf("Très bien, allons-y pour le niveau moyen\n");
                       creationMinuteur(30);
                       break;
                   case 3:
                       printf("Très bien, allons-y pour le niveau difficile\n");
                       printf("Grille avec les cibles et les robots :\n");
                       afficherMurs(rangees, colonnes);
                       creationMinuteur(20);
                       break;
                   default:
                       printf("L'entrée n'est pas valide.\n");
                       printf("Veuillez réessayer.\n");
                       break;
               }
           }
       } while (niveau < 1 || niveau > 3 || res != 1);





    printf("\033[H\033[J");
   int r = 0;

   for (int i = 0; i < nb_joueur; i++) {
       do{
         printf("%s : entre ton nombre de coups : ", joueurs[i].nom);
        res = scanf("%d", &joueurs[i].nbrcoup);
           if(res != 1 || joueurs[i].nbrcoup < 1){
                printf("Erreur veuillez saisir un nombre superieur ou égale à 1 \n");
                    }
           while (getchar() != '\n');
       }while(res != 1 || joueurs[i].nbrcoup < 1);
         if (joueurs[i].nbrcoup < joueurs[r].nbrcoup) {
             r = i;
         }
     }


   printf("Le joueur ayant le moins de coups (%d) commence.\n", joueurs[r].nbrcoup);
    printf("Voici le robot pour le Joueur %s : ", joueurs[r].nom);
    if (nb_joueur >= 1) {
        switch (r) {
            case 0:
                printf("🐧\n");
                break;
            case 1:
                printf("🐶\n");
                break;
            case 2:
                printf("🐱\n");
                break;
            case 3:
                printf("🐴\n");
                break;
            default:
                printf("Erreur dans la sélection du robot\n");
                exit(EXIT_FAILURE);


         }
        }

   afficherMurs(rangees, colonnes);


   Resultat resultat = {r, joueurs[r].nbrcoup, nb_joueur};
   return resultat;
}



char affichageCible(char c) {

  c = rand() % NB_CIBLES + 'A';
  printf("Voici la cible que vous devez atteindre : %c \n\n", c);

  printf("Bonne chance ;)\n\n");
  return c; // Ajouter cette ligne pour retourner la valeur de la cible
}

void creationMinuteur(int chrono){
  printf("Temps de réflexion : %d secondes\n", chrono);

for (int i = chrono; i>0; i--){
  sleep(1);
}
 printf("Temps de réflexion terminé \n");
}   






int deplacerRobot(int r, char c, Robot robots[], Cible cibles[], int deplacementsrobots) {
  char direction;
  bool atteintCible = false;


  while (!atteintCible) {
      printf("Entrez la direction pour déplacer le robot %d (Z = haut, S = bas, Q = gauche, D = droite) : ", r + 1);
      scanf(" %c", &direction);

      if (direction != 'Z' && direction != 'z' &&
          direction != 'Q' && direction != 'q' &&
          direction != 'S' && direction != 's' &&
          direction != 'D' && direction != 'd') {
          printf("Direction invalide. Veuillez entrer Z, Q, S ou D.\n");
          continue;
      }
       deplacementsrobots += 1;

      while (true) {
          int newX = robots[r].position.x;
          int newY = robots[r].position.y;

          switch (direction) {
              case 'Z':
              case 'z':
                  newX -= 1;
                  break;
              case 'S':
              case 's':
                  newX += 1;
                  break;
              case 'Q':
              case 'q':
                  newY -= 1;
                  break;
              case 'D':
              case 'd':
                  newY += 1;
                  break;
              default:
                  printf("Commande de direction non valide veuillez recommencer.\n");
          }

          if (newX < 0 || newX > MAX_RANGEES || newY < 0 || newY > MAX_COLONNES ||
              grille[newX][newY] == '#' || grille[newX][newY] == '*' || grille[newX][newY] == '+' ||
              grille[newX][newY] == '@' || grille[newX][newY] == '|' ||
              (grille[newX][newY] >= 'r' && grille[newX][newY] <= 'z')) {
              printf("Obstacle rencontré. Veuillez choisir une nouvelle direction.\n");
              printf("Nombre de coup : %d\n\n", deplacementsrobots);
              break;
          }

          grille[robots[r].position.x][robots[r].position.y] = '-';
          robots[r].position.x = newX;
          robots[r].position.y = newY;
          grille[newX][newY] = robots[r].symbole;

          // Affichage des coordonnées pour le débogage
          printf("Nouvelles coordonnées du robot : (%d, %d)\n", newX, newY);
          printf("Coordonnées de la cible : (%d, %d)\n", cibles[c - 'A'].position.x, cibles[c - 'A'].position.y);

          afficherMurs(MAX_RANGEES, MAX_COLONNES);
          //sleep(1);

          // Vérification si le robot atteint la cible
          if (newX == cibles[c - 'A'].position.x && newY == cibles[c - 'A'].position.y) {
              printf("Vous avez atteint la cible !\n");
              atteintCible = true;
              break;
          }

      }

  }
  return deplacementsrobots;
}