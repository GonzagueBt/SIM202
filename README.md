# SIM202

Le projet est muni d'un Makefile, un simple **make all** suffit à compiler l'ensemble et exécuter l'exemple dans la classe main.
Il y a plusieurs Obstacle "exemple" dans la classe le fichier _main.cpp_ qu'il est possible de combiner, modifer, en changeant simplement les points dans les fonctions de constructions des graphes.
Avec le **make all**, différents fichier _.txt_ sont générés, permettant, à l'aide de différents fichier _.m_ (matlab) d'afficher de différentes manières le graphe. Il suffit d’ouvrir le répertoire contenant le code, d’ouvrir un fichier .m et de cliquer sur run. Voici les différents affichage possible :  :
  - **Obstacle.m** : permet d'afficher tous les obstacles "brutes", non encore assemblés
  - **Graphe.m** : permet d'afficher le graphe avec tous les segments valides et la trajectoire optimale
  - **Trajectoire.m** : permet d'afficher le graphe avec uniquement la trajectoire optimale
  - **normale.m** : permet d'afficher un obstacle et ses normales
  - **concave.m** : permet d'afficher un obstacle concave avec tous ces segments valides entre ses sommets
