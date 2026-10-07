#include <stdio.h>
#include <stdlib.h>

#define UNIT_TEST
#include "../tri_bulles.c"

static int failures = 0;

static void check(const char *name, int *got, const int *expected, int n)
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
    int a_exp[] = {1, 3, 5, 6};
    bubbleSort(a, 4);
    check("tableau desordonne", a, a_exp, 4);

    int b[] = {1, 2, 3, 4};
    int b_exp[] = {1, 2, 3, 4};
    bubbleSort(b, 4);
    check("deja trie", b, b_exp, 4);

    int c[] = {9, 7, 5, 3, 1};
    int c_exp[] = {1, 3, 5, 7, 9};
    bubbleSort(c, 5);
    check("ordre inverse", c, c_exp, 5);

    int d[] = {4, 2, 4, 1, 2};
    int d_exp[] = {1, 2, 2, 4, 4};
    bubbleSort(d, 5);
    check("doublons", d, d_exp, 5);

    int e[] = {-3, 0, -10, 8};
    int e_exp[] = {-10, -3, 0, 8};
    bubbleSort(e, 4);
    check("valeurs negatives", e, e_exp, 4);

    int f[] = {42};
    int f_exp[] = {42};
    bubbleSort(f, 1);
    check("un seul element", f, f_exp, 1);

    bubbleSort(NULL, 0);   /* ne doit pas planter */
    bubbleSort(f, 0);      /* tableau vide */
    printf("[ OK ] cas limites (NULL, taille 0)\n");

    if (failures)
    {
        printf("%d test(s) en echec\n", failures);
        return EXIT_FAILURE;
    }
    printf("Tous les tests sont passes\n");
    return EXIT_SUCCESS;
}
