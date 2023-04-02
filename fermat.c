#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour vérifier si deux nombres sont premiers entre eux
int premiers(mpz_t x, mpz_t y) {
    mpz_t a, r, b;
    mpz_init(a);
    mpz_init(r);
    mpz_init(b);

    mpz_set(a, x);
    mpz_set(b, y);

    while (mpz_cmp_ui(b, 0) > 0) {
        mpz_mod(r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
    }

    if (mpz_cmp_ui(a, 1) == 0) {
        return 1;
    }

    return 0;
}

// Fonction pour tester la primalité en utilisant le test de Fermat
int Fermat(mpz_t n, mpz_t k) {
    gmp_randstate_t state;
    gmp_randinit_mt(state); // Initialise l'état pour un algorithme de Mersenne Twister
    gmp_randseed_ui(state, time(NULL));

    mpz_t i, n2, a, r, m;
    mpz_init(i);
    mpz_init(n2);
    mpz_init(a);
    mpz_init(r);
    mpz_init(m);

    mpz_set_si(i, 1);

    mpz_sub_ui(n2, n, 1);
    mpz_sub_ui(m, n, 3);

    while (mpz_cmp(i, k) <= 0) {
        if (mpz_cmp_si(n, 2) == 0 || mpz_cmp_si(n, 3) == 0) {
            break; // Prime
        }

        mpz_urandomm(a, state, m);
        mpz_add_ui(a, a, 2);

        if (premiers(a, n) == 1) {
            mpz_powm(r, a, n2, n);

            if (mpz_cmp_si(r, 1) != 0) {
                mpz_clear(i);
                mpz_clear(n2);
                mpz_clear(a);
                mpz_clear(r);
                mpz_clear(m);

                gmp_randclear(state);

                return 0;
            }
        }
        mpz_add_ui(i, i, 1);
    }

    mpz_clear(i);
    mpz_clear(n2);
    mpz_clear(a);
    mpz_clear(r);
    mpz_clear(m);

    gmp_randclear(state);

    return 1;
}

int main() {
    mpz_t n, k;
    int prime;

    mpz_init(n);
    mpz_init(k);

    printf("Choisir n : ");
    gmp_scanf("%Zd", &n);
    if (mpz_cmp_ui(n, 1) <= 0) {
        printf("\n Erreur nombre inférieur à 2");
    } else {
        printf("Choisir k : ");
        gmp_scanf("%Zd", &k);

        prime = Fermat(n, k);

        if (prime == 1)
            gmp_printf("*******************%Zd est premier******************* \n", n);
        else
            gmp_printf("*******************%Zd est composé******************* \n", n);
    }

    mpz_clear(n);
    mpz_clear(k);

    return 0;
}