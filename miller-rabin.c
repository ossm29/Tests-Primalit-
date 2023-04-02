#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// algorithme Square and Multiply
void square_and_multiply(mpz_t a, mpz_t n, mpz_t h, mpz_t y) {
    char *d = mpz_get_str(NULL, 2, h);
    int i;
    mpz_set(y, a);
    for (i = 1; i < strlen(d); i++) {
        mpz_mul(y, y, y);
        mpz_mod(y, y, n);
        if (d[i] == '1') {
            mpz_mul(y, y, a);
            mpz_mod(y, y, n);
        }
    }
}

// Fonction qui décompose (n-1) en d*2^s
void decompose(mpz_t n, mpz_t d, mpz_t s) {
    mpz_set(d, n);
    mpz_set_ui(s, 0);

    while (mpz_even_p(d) != 0) {
        mpz_divexact_ui(d, d, 2);
        mpz_add_ui(s, s, 1);
    }
}

// Fonction pour exécuter l'algorithme de Miller-Rabin
int miller_rabin(mpz_t n, int k) {
    if (mpz_cmp_ui(n, 2) <= 0) {
        return mpz_cmp_ui(n, 2) == 0;
    }
    if (mpz_even_p(n) != 0) {
        return 0;
    }

    mpz_t d, s, a, x, n_minus_1, n_minus_3;
    mpz_inits(d, s, a, x, n_minus_1, n_minus_3, NULL);
    mpz_sub_ui(n_minus_1, n, 1);
    mpz_sub_ui(n_minus_3, n, 3);

    decompose(n_minus_1, d, s);

    gmp_randstate_t rand_state;
    gmp_randinit_mt(rand_state);
    gmp_randseed_ui(rand_state, time(NULL));

    for (int i = 0; i < k; ++i) {
        mpz_urandomm(a, rand_state, n_minus_3);
        mpz_add_ui(a, a, 2);

        mpz_powm(x, a, d, n);

        if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_minus_1) == 0) {
            continue;
        }

        int j;
        for (j = 1; j < mpz_get_ui(s); ++j) {
            mpz_powm_ui(x, x, 2, n);

            if (mpz_cmp_ui(x, 1) == 0) {
                break;
            }
            if (mpz_cmp(x, n_minus_1) == 0) {
                break;
            }
        }

        if (mpz_cmp(x, n_minus_1) != 0) {
            mpz_clears(d, s, a, x, n_minus_1, n_minus_3, NULL);
            gmp_randclear(rand_state);
            return 0;
        }
    }

    mpz_clears(d, s, a, x, n_minus_1, n_minus_3, NULL);
    gmp_randclear(rand_state);
    return 1;
}

int main() {
    mpz_t n;
    int k;

    mpz_init(n);

    printf("Choisir n : ");
    gmp_scanf("%Zd", &n);
    printf("Choisir k : ");
    scanf("%d", &k);

    int result = miller_rabin(n, k);
    if (result == 1) {
        gmp_printf("******************* %Zd est probablement premier *******************\n",n);
    } else {
        gmp_printf("******************* %Zd est composé *******************\n",n);
    }

    mpz_clear(n);
    return 0;
}
