# Tests de primalité de Fermat et Miller-Rabin

Ceci est une implémentation des tests de primalité (*vérifier si un nombre est premier*) de Fermat et de Miller-Rabin en utilisant la librairie GMP en C. 
Ces deux tests sont très utilisés en cryptographie .

## Utilisation

Suivez les instructions à l'écran pour saisir les valeurs de `n` et `k`.
- n : nombre à tester
- k : nombre d'itérations pour les tests de primalité
![](https://i.imgur.com/thlUrsE.png)


## Structure du projet

Le projet est composé de deux fichiers principaux :

1. `fermat.c` : Implémentation du test de primalité de Fermat.
2. `miller-rabin.c` : Implémentation du test de primalité de Miller-Rabin.

## Compilation et exécution

### Prérequis

Assurez-vous d'avoir installé la librairie GMP sur votre système.

### Compilation

Pour compiler les fichiers, exécutez les commandes suivantes :

```
gcc fermat.c -o fermat -lgmp
gcc miller-rabin.c -o miller-rabin -lgmp
````

### Exécution

Pour exécuter les programmes, utilisez les commandes suivantes :

```
./fermat
./miller-rabin
```
