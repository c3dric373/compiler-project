int pair(int valeur) {
    int resultat;
    if(valeur==0){
        return 1 ;
    }
    else {
        int x = valeur-1;
        resultat=impair(x);
        return resultat;
    }
}

int impair(int valeur) {
    int resultat;
    if(valeur==1){
        return 1;
    }
    else {
        if(valeur==0){
            return 0;
        }
        int x = valeur-1;
        resultat=pair(x);
        return resultat;
    }
}

int main() {
    int a = 22;
    int b;
    b = pair(a);
    return b;
}