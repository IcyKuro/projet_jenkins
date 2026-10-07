#include <stdio.h>

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
        /* Les i derniers elements sont deja a leur place. */
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

#ifndef UNIT_TEST /* le main est exclu lors de la compilation des tests */
int main(void)
{
    int arr[] = {5, 6, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
#endif
