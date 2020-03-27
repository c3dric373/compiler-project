# Guide d'utilisation des livrabes de mi-parcours PLD COMP H4222

## Utiliser le "compilateur" ifcc dans le dossier compiler
L'utilisation du compilateur est relativement simple :
```
./ifcc fichier.c
```
Cet executable génère le fichier assembleur fichier.s qui pourra être utilisé plus tard pour créer un executable (en utilisant gcc par exemple)

## Utiliser le script execute dans le fichier compiler
Le script `execute.sh` compile le fichier c fourni en argument et l'execute ( en utilisant donc l'excecutable `./ifcc` pour généré le code assembleur qui sera traité avec gcc)
On le lance en tapant la ligne suivante :
```
./execute.sh fichier.c
```
ou

```
sh execute.sh fichier.c
```

## Utiliser les scripts de test dans le fichier test
Le fichier `test.sh` à executer avec docker se nomme test.sh et s'execute sans entrée.
Il lance les script python `pld-test.py` qui va effectuer les tests en comparant les resultats du compilateur crée avec le compilateur gcc en utilisant `pld_wrapper.sh`  :
On le lance simplement ainsi : 
```
./test.sh 
```

Le fichier `test_if.sh` lance le script python `pld-test.py` sans passer par docker et supprime le dossier de sortie `pld_test_output`

Le fichier `test_if_log.sh` fonctionne comme `test_if.sh` sauf qu'il conserve `pld_test_output`
