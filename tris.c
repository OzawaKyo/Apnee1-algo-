#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NMAX 50000 /* peut etre modifie si necessaire */

/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    t[i] = rand();
  };
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n)
{
  int i;
  int x = 0;

  for (i = 0; i < n; i++)
  {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
long int tri_insertion(int t[], int n)
{
  int i, j;
  int Clef;
  long int count = 0;

  for (i = 1; i < n; i++)
  {

    Clef = t[i];

    j = i - 1;

    /* Decalage des valeurs du tableau */
    while ((j >= 0))
    {
      count++;
      if (t[j] <= Clef)
      {
        break;
      }
      t[j + 1] = t[j];
      j = j - 1;
    }
    /* insertion de la clef */
    t[j + 1] = Clef;
  }
  return count;
}

void Echange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int t[], int g, int d, long int *count)
{
    int pivot = t[d];
    int i = g - 1;

    for (int j = g; j < d; j++)
    {
        (*count)++;
        if (t[j] <= pivot)
        {
            i++;
            Echange(&t[i], &t[j]);
        }
    }
    Echange(&t[i + 1], &t[d]);
    return i + 1;
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
long int tri_segmentation(int t[], int g, int d)
{
    long int count = 0;
    if (g < d)
    {
        int p = Partition(t, g, d, &count);
        count += tri_segmentation(t, g, p - 1);
        count += tri_segmentation(t, p + 1, d);
    }
    return count;
}

void lancer_mesures()
{
  int valeurs_N[] = {100, 500, 1000, 5000, 10000, 25000, 40000, 50000}; // Valeurs de N à tester
  int taille_N = 8;                                       // Nombre de valeurs de N
  int K = 100;                                             // Nombre d'exécutions par taille de tableau

  int T[NMAX];
  srand(12345); // Initialiser le générateur aléatoire avec un germe fixe

  printf("Tri par insertion ou par segmentation ? (i/s) ");
  char choix;
  while (1)
  {
    scanf(" %c", &choix);
    if (choix == 'i' || choix == 's')
    {
      break;
    }
    printf("Choix invalide. Veuillez entrer 'i' ou 's' : ");
  }
    
  printf("quel type de generation aleatoire ? (u/n) ");
  char type_generation;

  while (1)
  {
    scanf(" %c", &type_generation);
    if (type_generation == 'u' || type_generation == 'n')
    {
      break;
    }
    printf("Choix invalide. Veuillez entrer 'u' ou 'n' : ");
  }

  for (int i = 0; i < taille_N; i++)
  {
    int N = valeurs_N[i];
    long long total_comparaisons = 0;
    double total_temps = 0;
    for (int j = 0; j < K; j++)
    {
      if (type_generation == 'u')
      {
        generation_aleatoire(T, N);
      }
      else
      {
        generation_aleatoire_non_uniforme(T, N);
      }
      clock_t debut = clock();
      if (choix == 'i')
      {
        total_comparaisons += tri_insertion(T, N);
      }
      else
      {
        total_comparaisons += tri_segmentation(T, 0, N - 1);
      }
      clock_t fin = clock();
      double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
      total_temps += temps;
    }

    double moyenne_comparaisons = (double)total_comparaisons / K;
    // double temps_moyen = total_temps / K;

    // // Affichage des résultats sous forme de tableau
    // printf("%d %f %f\n", N, moyenne_comparaisons, temps_moyen);

    //afficher les resultats pour gnu plot , en utilisant le format suivant : N comparaisons (separe par des espaces) , avec 2 chiffres apres la virgule
    printf("%d %.2f\n", N, moyenne_comparaisons);
  }
}
