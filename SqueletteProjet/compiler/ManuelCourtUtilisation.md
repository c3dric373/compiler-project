# README 

Pour utiliser le compilateur il faut tout d'abord se rendre dans le dossier: `compiler`. 
```
cd compiler
```
Puis il faut compiler notre compilateur. Pour ceci il suffit de faire un simple: 
```
make
```

## Utiliser le compilateur ifcc
Une fois le compilateur créé, son utilisation est relativement simple :
```
./ifcc fichier.c
```
Cette commande génère le fichier assembleur fichier.s qui pourra être utilisé plus tard pour créer un executable (en utilisant gcc par exemple)

Nous avons implementé certains scripts: qui facilite l'utilisation:
### Execute
Le script `execute.sh` utilise notre compilateur pour compiler un fichier nommé `ret42.c`. De plus il compilera le fichier `ret42.s`, qui a été créé par notre compilateur, avec gcc. Finalement la valeur retourné par la compilation sera affiché dans le terminal. 
```
./execute.sh
```
### Run_gcc
Ce script compile simplement le fichier `ret42.c` avec gcc et affiche son résultat dans le terminal. 
```
./run_gcc.sh
```

### Test
Ce script (`test.sh`) permet d'afficher les résultats des deux scripts précédants, afin de pouvoir comparer les deux compilateur plus facilement. 
```
./test.sh
```

## Environnement de test
L'environnement de test se trouve sous: `/test`.
Le fichier `test.sh` à executer avec docker se nomme test.sh et s'execute sans entrée.
Il lance les script python `pld-test.py` qui va effectuer les tests en comparant les resultats du compilateur crée avec le compilateur gcc en utilisant `pld_wrapper.sh`  :
On le lance simplement ainsi : 
```
./test.sh 
```

Le fichier `test_if.sh` lance le script python `pld-test.py` sans passer par docker et supprime le dossier de sortie `pld_test_output`

Le fichier `test_if_log.sh` fonctionne comme `test_if.sh` sauf qu'il conserve `pld_test_output`
