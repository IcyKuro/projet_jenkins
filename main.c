#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "tri_bulles.h"

static const int DEFAULT_VALUES[] = {5, 6, 1, 3};
static const int DEFAULT_COUNT = sizeof(DEFAULT_VALUES) / sizeof(DEFAULT_VALUES[0]);

/* Convertit un argument en int, refuse tout ce qui n'est pas un entier valide. */
static int parseInt(const char *text, int *out)
{
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || value < INT_MIN || value > INT_MAX)
        return 0;
    *out = (int)value;
    return 1;
}

/* Sans argument : trie le tableau du sujet. Avec arguments : trie les entiers fournis. */
int main(int argc, char *argv[])
{
    int count = argc > 1 ? argc - 1 : DEFAULT_COUNT;
    /* Allocation dynamique pour que valgrind (memcheck) ait du tas a surveiller. */
    int *arr = malloc((size_t)count * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Allocation impossible\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++)
    {
        if (argc == 1)
            arr[i] = DEFAULT_VALUES[i];
        else if (!parseInt(argv[i + 1], &arr[i]))
        {
            fprintf(stderr, "Argument invalide : %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
    }

    bubbleSort(arr, count);

    for (int i = 0; i < count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return EXIT_SUCCESS;
}
