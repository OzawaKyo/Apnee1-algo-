#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NMAX 50000 /* peut etre modifie si necessaire */

void generation_aleatoire(int t[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    t[i] = rand();
  };
}

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

long int tri_insertion_count(int t[], int n)
{
  int i, j;
  int Clef;
  long int count = 0;

  for (i = 1; i < n; i++)
  {
    Clef = t[i];
    j = i - 1;

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
    t[j + 1] = Clef;
  }
  return count;
}

void tri_insertion(int t[], int n)
{
  tri_insertion_count(t, n);
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

long int tri_segmentation_rec(int t[], int g, int d)
{
    long int count = 0;
    if (g < d)
    {
        int p = Partition(t, g, d, &count);
        count += tri_segmentation_rec(t, g, p - 1);
        count += tri_segmentation_rec(t, p + 1, d);
    }
    return count;
}

void tri_segmentation(int t[], int n)
{
    tri_segmentation_rec(t, 0, n - 1);
}

void lancer_mesures()
{
  int valeurs_N[] = {100, 500, 1000, 5000, 10000, 25000, 40000, 50000};
  int taille_N = 8;
  int K = 100;

  int T[NMAX];
  srand(12345);

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
        total_comparaisons += tri_insertion_count(T, N);
      }
      else
      {
        total_comparaisons += tri_segmentation_rec(T, 0, N - 1);
      }
      clock_t fin = clock();
      double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
      total_temps += temps;
    }

    double moyenne_comparaisons = (double)total_comparaisons / K;
    printf("%d %.2f\n", N, moyenne_comparaisons);
  }
}