#include "header.h"

int main() {
    char n;
    int nbManches, joueurCourant, deplacementsCourants, nb_joueur;
    int deplacementsrobots = 0;
    Joueur joueurs[JEJ];
    int res;
    Resultat resultat;
    char grille[MAX_RANGEES + 1][MAX_COLONNES + 1];

    do {
        printf("Entrez le nombre de manches : ");
    res = scanf("%d", &nbManches);
    if (nbManches < 1 || res != 1) {
        printf("Erreur veuillez saisir un chiffre ou un nombre superieur à 1.\n");
       while (getchar() != '\n');
    }
       } while(nbManches < 1 || res != 1);

    for (int manche = 0; manche < nbManches; manche++) {
        printf("\n=== Manche %d ===\n", manche + 1);

        int rangees = rand() % 6 + 25;
        int colonnes = rand() % 6 + 25;

        initialiserGrille(rangees, colonnes);
        Cible cibles[NB_CIBLES];
        placerCibles(cibles);
        Robot robots[NB_ROBOTS];
        placerRobots(robots);
        char c = affichageCible(c);
        Resultat resultat = affichageElements(robots, joueurs, joueurCourant, manche, rangees, colonnes);
        int r = resultat.joueurIndex;
        int nbrcoup = resultat.nbrcoup;
        int nb_joueur = resultat.nb_joueur;
        deplacementsrobots = deplacerRobot(r, c, robots, cibles, deplacementsrobots);
        mettreAJourScores(joueurs, joueurCourant, nbrcoup, deplacementsrobots, r, nb_joueur);
        afficherScores(joueurs, nb_joueur, n);
    }
    return 0;
}