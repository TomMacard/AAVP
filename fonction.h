/*
 * Fichier: fonction.h
 * Auteur: Tom MACARD
 * ---------------------
 * Fichier header contenant les structures et les signatures des fonctions
 * de création d'arbres et de vérification de leur nature (ABR / Non ABR)
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>


// Définition de la structure pour un noeud d'ABR
struct Noeud {
    int valeur;
    struct Noeud* gauche;
    struct Noeud* droite;
};

//Structure pile pour la version itérative
struct PileElement {
    struct Noeud* noeud;
    int min;
    int max;
};

struct Foret {
    struct Noeud* arbre;
    struct Foret* suivant;
};

#define TAILLE_PILE 100000


// Fonctions

struct Noeud* creerNoeud(int valeur);
bool estABR_recursif(struct Noeud* arbre, int min, int max);
bool estABR_iteratif(struct Noeud* arbre);
struct Noeud* creer_ABR(int taille);
struct Noeud* creer_non_ABR(int taille);
struct Noeud* creer_AB_aleatoire(int taille);