#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define MAX_RANGEES 40
#define MAX_COLONNES 40
#define NB_CIBLES 18
#define NB_ROBOTS 4
#define JEJ 10

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char symbole;
    Position position;
    int numero;
    Position cibleFinale;
} Cible;

typedef struct {
    char symbole;
    Position position;
    char couleur;
    int chiffre;
} Robot;

typedef struct {
    char nom[50];
    int score;
    int nbrcoup;
} Joueur;

typedef struct {
    int joueurIndex;
    int nbrcoup;
    int nb_joueur;
} Resultat;

void couleur(const char* param);
void creationMinuteur(int chrono);
void mettreAJourScores(Joueur joueurs[], int joueurCourant, int nbrcoup, int deplacementsrobots, int r, int nb_joueurs);
int obtenirGagnant(Joueur joueurs[], int nb_joueurs);
void afficherScores(Joueur joueurs[], int nb_joueur, char n);
void initialiserGrille(int rangees, int colonnes);
void placerCibles(Cible cibles[]);
void placerRobots(Robot robots[]);
void afficherMurs(int rangees, int colonnes);
Resultat affichageElements(Robot robots[], Joueur joueurs[], int joueurCourant, int manche, int rangees, int colonnes);
char affichageCible(char c);
int deplacerRobot(int r, char c, Robot robots[], Cible cibles[], int deplacementsrobots);

#endif /* HEADER_H */