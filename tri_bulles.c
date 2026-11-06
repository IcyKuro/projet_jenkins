#include <stdbool.h>
#include <stddef.h>
#include "tri_bulles.h"

/* Echange les elements d'indices i et j du tableau. */
void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/* Tri a bulles (ordre croissant). Ne fait rien si arr est NULL ou n <= 1. */
void bubbleSort(int arr[], int n)
{
    if (arr == NULL)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        bool hasSwapped = false;
        /* Les i derniers elements sont deja a leur place. */
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr, j, j + 1);
                hasSwapped = true;
            }
        }
        /* Aucun echange sur ce passage : le tableau est deja trie, inutile de continuer. */
        if (!hasSwapped)
            return;
    }
}
