/*
 * Fichier: fonction.c
 * Auteur: Tom MACARD
 * ---------------------
 * Fichier contenants les fonctions de création d'arbres et 
 * de vérification de leur nature (ABR / Non ABR)
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "fonction.h"


// Fonction utilitaire pour créer un nouveau noeud
struct Noeud* creerNoeud(int valeur) {
    struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
    nouveauNoeud->valeur = valeur;
    nouveauNoeud->gauche = nouveauNoeud->droite = NULL;
    return nouveauNoeud;
}


// Fonction récursive pour la validation de l'ABR
bool estABR_recursif(struct Noeud* arbre, int min, int max) {
    // Cas de base : arbre vide est un ABR
    if (arbre == NULL)
        return true;

    // Vérifie si la valeur du noeud est dans la plage autorisée
    if (arbre->valeur < min || arbre->valeur > max)
        return false;

    // Vérifie les sous-arbres gauche et droit récursivement
    return (estABR_recursif(arbre->gauche, min, arbre->valeur - 1) &&
            estABR_recursif(arbre->droite, arbre->valeur + 1, max));
}


// Fonction itérative pour la validation de l'ABR
bool estABR_iteratif(struct Noeud* arbre) {
    if (arbre == NULL)
        return true;

    // Utilisation d'une pile pour la traversée en profondeur
    struct PileElement pile[TAILLE_PILE]; // Taille arbitraire
    int sommet = -1; // Initialisation de la pile

    // Empile le noeud racine avec les plages autorisées
    pile[++sommet] = (struct PileElement){arbre, 0, INT_MAX};

    while (sommet >= 0) {
        // Dépile un élément de la pile
        struct PileElement element = pile[sommet--];
        struct Noeud* noeud = element.noeud;
        int min = element.min;
        int max = element.max;

        // Vérifie si la valeur du noeud est dans la plage autorisée
        if (noeud->valeur < min || noeud->valeur > max)
            return false;

        // Empile le sous arbre droit avec la plage autorisée mise à jour
        if (noeud->droite != NULL)
            pile[++sommet] = (struct PileElement){noeud->droite, noeud->valeur + 1, max};

        // pareil à gauche
        if (noeud->gauche != NULL)
            pile[++sommet] = (struct PileElement){noeud->gauche, min, noeud->valeur - 1};
    }

    return true;
}

struct Noeud* creer_ABR(int taille) {
    struct Noeud* arbre = creerNoeud(taille / 2);
    for (int i = 0; i < taille / 2; i++) {
        arbre->gauche = creerNoeud(i);
        arbre->droite = creerNoeud(taille - i);
    }
    return arbre;
}

struct Noeud* creer_non_ABR(int taille) {
    struct Noeud* arbre = creerNoeud(taille / 2);
    for (int i = 0; i < taille / 2; i++) {
        if (i == taille/4) {
            // noeud qui va casser l'ABR
            arbre->gauche = creerNoeud(INT_MAX);
            arbre->droite = creerNoeud(INT_MAX);
        }
        else {
            arbre->gauche = creerNoeud(i);
            arbre->droite = creerNoeud(taille - i);
        }
    } 
    return arbre;
}


struct Noeud* creer_AB_aleatoire(int taille) {
    struct Noeud* arbre = creerNoeud(taille / 2);
    for (int i = 0; i < taille / 2; i++) {
        arbre->gauche = creerNoeud(rand() % INT_MAX);
        arbre->droite = creerNoeud(rand() % INT_MAX);
    }
    return arbre;
}

