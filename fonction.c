#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "fonction.h"




// Fonction utilitaire pour créer un nouveau nœud
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

    // Vérifie si la valeur du nœud est dans la plage autorisée
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
    struct PileElement pile[1000]; // Taille arbitraire de la pile
    int sommet = -1; // Initialisation de la pile

    // Empile le nœud racine avec les plages autorisées
    pile[++sommet] = (struct PileElement){arbre, INT_MIN, INT_MAX};

    while (sommet >= 0) {
        // Dépile un élément de la pile
        struct PileElement element = pile[sommet--];
        struct Noeud* noeud = element.noeud;
        int min = element.min;
        int max = element.max;

        // Vérifie si la valeur du nœud est dans la plage autorisée
        if (noeud->valeur < min || noeud->valeur > max)
            return false;

        // Empile le sous-arbre droit avec la plage autorisée mise à jour
        if (noeud->droite != NULL)
            pile[++sommet] = (struct PileElement){noeud->droite, noeud->valeur + 1, max};

        // Empile le sous-arbre gauche avec la plage autorisée mise à jour
        if (noeud->gauche != NULL)
            pile[++sommet] = (struct PileElement){noeud->gauche, min, noeud->valeur - 1};
    }

    return true;
}