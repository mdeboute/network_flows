# network_flows

Implémentation d'algorithmes de théorie des graphes ainsi que la structure de données en C++ (*cf. Network Flows, Ahuja et al*)

## Comment compiler et exécuter le programme ?

```shell
mkdir build
cd build
cmake ..
make
./a.out
```

## Ressources

Netflow : [ici](http://archive.dimacs.rutgers.edu/pub/netflow/generators/network/)

Ce répertoire contient des programmes qui génèrent des réseaux et des graphes.
La plupart sont au format DIMACS, [ceci](http://lpsolve.sourceforge.net/5.5/DIMACS_maxf.htm) est un site Web pour en savoir plus sur ce format.

## Travail minimum requis (deadline: 18/02/2022)

### Implémenter 3 algorithmes

#### Deux de flots max

- 1 avec chemins augmantants pour flot max : successive shortest path en O(n^2m) et/ou labeling algo en O(nmU), pseudo-polynomiale
- 1 flot maximum avec pré-flots : FIFO pre-flow push algo en O(n^3)

#### Un de coup min

- 1 flot de coût minimum : cycle cancelling en O(mCU), out-of-kilter en O(nu) (en priorité) et en complexité polynomiale on a le minimum mean-cycle cancelling algo en O(n^2m^3log(n)) (lui il est compliqué)

#### Faire un checker/evaluator

#### Modéliser les problèmes sous forme de PL avec Gurobi ou CPLEX ou OR-Tools
