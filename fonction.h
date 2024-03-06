#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>


// Définition de la structure pour un nœud d'ABR
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


// Fonctions

struct Noeud* creerNoeud(int valeur);
bool estABR_recursif(struct Noeud* arbre, int min, int max);
bool estABR_iteratif(struct Noeud* arbre);