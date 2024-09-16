#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define NMAX 50000		/* peut etre modifie si necessaire */



/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n) {
  int i ;

  for (i=0 ; i<n ; i++) {
	  t[i] = rand() ;
  } ;
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n) {
  int i;
  int x = 0;

  for (i=0; i < n; i++) {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
int tri_insertion(int t[], int n) {
  int i,j;
  int Clef;
  int count = 0;

  for(i=1; i < n; i++) {
    
    Clef = t[i];
    
    j = i - 1;
    
    /* Decalage des valeurs du tableau */
    while((j >= 0) ) {
      count++;
      if(t[j] <= Clef) {
        break;
      }
      t[j+1] = t[j];
      j = j - 1;
    }
    /* insertion de la clef */
    t[j+1] = Clef;
  }
  return count;
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_segmentation(int t[], int n) {
  /* A completer */
}



void lancer_mesures() {
  int T[NMAX];
  int K, N;
  // unsigned int germe;

  // printf("Valeur du germe pour la fonction de tirage aleatoire ? ");
  // scanf("%d", &germe);
  // srand(germe);

  printf("Nombre d'exécutions (K) ? ");
  scanf("%d", &K);

  printf("Taille du tableau (N) ? ");
  scanf("%d", &N);

  if (N > NMAX) {
    printf("Erreur : N ne peut pas dépasser %d\n", NMAX);
    return;
  }

  long long total_comparaisons = 0;
  clock_t debut = clock();

  for (int k = 0; k < K; k++) {
    generation_aleatoire(T, N);
    total_comparaisons += tri_insertion(T, N);
  }

  clock_t fin = clock();
  double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
  double moyenne_comparaisons = (double)total_comparaisons / K;

  printf("N = %d, K = %d\n", N, K);
  printf("Moyenne des comparaisons = %.2f\n", moyenne_comparaisons);
  printf("Temps total = %.2f secondes\n", temps);
  printf("Temps moyen par exécution = %.6f secondes\n", temps / K);
}
