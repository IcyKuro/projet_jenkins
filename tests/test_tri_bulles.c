#include <stdio.h>
#include <stdlib.h>
#include "../tri_bulles.h"

static int failures = 0;

static void check(const char *name, const int *got, const int *expected, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (got[i] != expected[i])
        {
            printf("[FAIL] %s (index %d : obtenu %d, attendu %d)\n", name, i, got[i], expected[i]);
            failures++;
            return;
        }
    }
    printf("[ OK ] %s\n", name);
}

int main(void)
{
    int a[] = {5, 6, 1, 3};
    bubbleSort(a, 4);
    check("tableau du sujet", a, (int[]){1, 3, 5, 6}, 4);

    int b[] = {1, 2, 3, 4};
    bubbleSort(b, 4);
    check("deja trie", b, (int[]){1, 2, 3, 4}, 4);

    int c[] = {9, 7, 5, 3, 1};
    bubbleSort(c, 5);
    check("ordre inverse", c, (int[]){1, 3, 5, 7, 9}, 5);

    int d[] = {4, 2, 4, 1, 2};
    bubbleSort(d, 5);
    check("doublons", d, (int[]){1, 2, 2, 4, 4}, 5);

    int e[] = {-3, 0, -10, 8};
    bubbleSort(e, 4);
    check("valeurs negatives", e, (int[]){-10, -3, 0, 8}, 4);

    int f[] = {42};
    bubbleSort(f, 1);
    check("un seul element", f, (int[]){42}, 1);

    bubbleSort(NULL, 0);
    bubbleSort(f, 0);
    check("tableau vide ou NULL", f, (int[]){42}, 1);

    int g[] = {1, 2};
    swap(g, 0, 1);
    check("swap", g, (int[]){2, 1}, 2);

    if (failures)
    {
        printf("%d test(s) en echec\n", failures);
        return EXIT_FAILURE;
    }
    printf("Tous les tests sont passes\n");
    return EXIT_SUCCESS;
}
