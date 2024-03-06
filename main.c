#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>

#include "fonction.h"




int main() {

    // Déclaration des variables
    double w1;
    double w2;
    bool resultatRecursif;
    bool resultatIteratif;
    double tempsRecursif;
    double tempsIteratif;


    // Création de l'arbre
    struct Noeud* arbre = creerNoeud(2);
    arbre->gauche = creerNoeud(1);
    arbre->droite = creerNoeud(3);


    // Calculs
    w1 = omp_get_wtime();
    resultatRecursif = estABR_recursif(arbre, INT_MIN, INT_MAX);
    w2 = omp_get_wtime();
    tempsRecursif = w2 - w1;

    w1 = omp_get_wtime();
    resultatIteratif = estABR_iteratif(arbre);
    w2 = omp_get_wtime();
    tempsIteratif = w2 - w1;


    // Résultats
        printf("Temps récursif    : %f\n", tempsRecursif);
    if (resultatRecursif)
        printf("Résultat recursif : Oui ABR\n");
    else
        printf("Résultat recursif : Non ABR\n");

        printf("Temps itératif    : %f\n", tempsIteratif);
    if (resultatIteratif)    
        printf("Résultat itératif : Oui ABR\n");
    else
        printf("Résultat itératif : Non ABR\n");

    return 0;
}
